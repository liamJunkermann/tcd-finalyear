from datetime import datetime, timedelta
import time
import boto3
import boto3.dynamodb
import boto3.dynamodb.types
import boto3.resources
from requests import request

import os
from dotenv import load_dotenv

Deserializer = boto3.dynamodb.types.TypeDeserializer()
Serializer = boto3.dynamodb.types.TypeSerializer()


class Accessor:
    # dynamoClient = None
    # c2ClientId = ""
    # c2ClientSecret = ""
    # stravaClientId = ""
    # stravaClientSecret = ""

    def __init__(self, awsAccessKey, awsSecretKey, c2ClientId, c2ClientSecret, stravaClientId, stravaClientSecret):
        if not awsAccessKey:
            load_dotenv()
            awsAccessKey = os.getenv("AWS_ACCESS_KEY")
            awsSecretKey = os.getenv("AWS_SECRET_KEY")
            c2ClientId = os.getenv("C2_CLIENT_ID")
            c2ClientSecret = os.getenv("C2_CLIENT_SECRET")
            stravaClientId = os.getenv("STRAVA_CLIENT_ID")
            stravaClientSecret = os.getenv("STRAVA_CLIENT_SECRET")

        if not awsAccessKey:
            raise ValueError("AWS Access Key not provided")
        if not awsSecretKey:
            raise ValueError("AWS Secret Key not provided")
        if not c2ClientId:
            raise ValueError("C2 Client ID not provided")
        if not c2ClientSecret:
            raise ValueError("C2 Client Secret not provided")
        if not stravaClientId:
            raise ValueError("Strava Client ID not provided")
        if not stravaClientSecret:
            raise ValueError("Strava Client Secret not provided")

        self.dynamoClient = boto3.client('dynamodb',
                                         region_name="eu-west-1",
                                         aws_access_key_id=awsAccessKey,
                                         aws_secret_access_key=awsSecretKey)
        self.c2ClientId = c2ClientId
        self.c2ClientSecret = c2ClientSecret
        self.stravaClientId = stravaClientId
        self.stravaClientSecret = stravaClientSecret

        print(self)

        boto3.resource('dynamodb', region_name="eu-west-1")
        return

    def time_from_ordinal(ordinal, _epoch=datetime(1900, 1, 1)):
        return _epoch + timedelta(days=ordinal)

    def getStravaUserToken(self, user_id):
        response = self.dynamoClient.get_item(
            TableName='StravaAccess-fyk5pm7xzrda5gk6pbibykvk6a-dev',
            Key={"athleteId": {"S": user_id}},
            AttributesToGet=[
                "access_token", "refresh_token", "expires_at"
            ]
        )

        data = {k: Deserializer.deserialize(v)
                for k, v in response["Item"].items()}

        return data

    def getNewStravaAccessToken(self, refresh_token):
        url = "https://www.strava.com/api/v3/oauth/token"

        payload = 'client_id='+self.stravaClientId+'&client_secret='+self.stravaClientSecret + \
            '&grant_type=refresh_token&refresh_token='+refresh_token
        headers = {
            'Content-Type': 'application/x-www-form-urlencoded',
        }

        response = request("POST", url, headers=headers, data=payload)
        return response

    def updateStravaUserToken(self, user_id, new_token):
        response = self.dynamoClient.update_item(
            TableName='StravaAccess-fyk5pm7xzrda5gk6pbibykvk6a-dev',
            Key={"athleteId": {"S": user_id}},
            ExpressionAttributeValues={
                ":"+k: Serializer.serialize(v) for k, v in new_token.items()
            },
            UpdateExpression="SET access_token = :access_token, refresh_token = :refresh_token, expires_at = :expires_at, expires_in = :expires_in, token_type = :token_type",
            ReturnValues="ALL_NEW",
        )

        return response

    def getNewC2AccessToken(self, refresh_token):
        url = "https://log.concept2.com/oauth/access_token"

        payload = 'client_id='+self.c2ClientId+'&client_secret='+self.c2ClientSecret + \
            '&grant_type=refresh_token&scope=user%3Aread%2Cresults%3Aread&refresh_token='+refresh_token
        headers = {
            'Content-Type': 'application/x-www-form-urlencoded',
        }

        response = request("POST", url, headers=headers, data=payload)

        return response

    def updateC2AccessToken(self, user_id: str, new_token: any):
        response = self.dynamoClient.update_item(
            TableName='C2Access-fyk5pm7xzrda5gk6pbibykvk6a-dev',
            Key={"user_id": {"S": user_id}},
            ExpressionAttributeValues={
                ":"+k: Serializer.serialize(v) for k, v in new_token.items()
            },
            UpdateExpression="SET access_token = :access_token, refresh_token = :refresh_token, expires_in = :expires_in, token_type = :token_type",
            ReturnValues="ALL_NEW",
        )
        return response

    def getUpdatedAccessToken(self, user_id: str, source="C2"):
        """A function to get and (if needed) update the access token for a user's connection"""
        key = ""
        match source:
            case "C2":
                key = "user_id"
            case "Polar":
                key = "x_user_id"
            case "Strava":
                key = "athleteId"

        print("key:", key, "user_id", user_id)

        response = self.dynamoClient.get_item(
            TableName=source+"Access-fyk5pm7xzrda5gk6pbibykvk6a-dev",
            Key={key: {"S": user_id}},
        )

        data = {k: Deserializer.deserialize(v)
                for k, v in response["Item"].items()}

        if (data['_lastChangedAt'] and data['expires_in']) or data["expires_at"]:
            expires_at = 0
            if "expires_at" in data.keys():
                expires_at = data["expires_at"]
            else:
                expires_at = (data['_lastChangedAt']/1000) + data['expires_in']
            # print("expires at:", int(expires_at), int(time.time()))
            if int(expires_at) < int(time.time()):
                print('expired, getting new token')
                print('got refresh token', data['refresh_token'])
                # Get new token & update
                new_token = {}
                match source:
                    case "C2":
                        new_token = self.getNewC2AccessToken(
                            data['refresh_token'])
                        print("newC2Token", new_token.json())
                        self.updateC2AccessToken(user_id, new_token.json())
                    case "Polar":
                        key = "x_user_id"
                    case "Strava":
                        print(data["refresh_token"])
                        new_token = self.getNewStravaAccessToken(
                            data['refresh_token'])
                        print("newStravaToken", new_token)
                        if new_token.status_code == 200:
                            self.updateStravaUserToken(
                                user_id, new_token.json())
                        else:
                            print("Error getting new token")
                            print(new_token.json())

                return new_token.json()

        return data


def main():
    import os
    from dotenv import load_dotenv

    AWS_ACCESS_KEY = os.getenv("AWS_ACCESS_KEY")
    AWS_SECRET_KEY = os.getenv("AWS_SECRET_KEY")
    C2_CLIENT_ID = os.getenv("C2_CLIENT_ID")
    C2_CLIENT_SECRET = os.getenv("C2_CLIENT_SECRET")
    STRAVA_CLIENT_ID = os.getenv("STRAVA_CLIENT_ID")
    STRAVA_CLIENT_SECRET = os.getenv("STRAVA_CLIENT_SECRET")

    LJStravaUserID = "32811115"
    accesor = Accessor(
        AWS_ACCESS_KEY,
        AWS_SECRET_KEY,
        C2_CLIENT_ID,
        C2_CLIENT_SECRET,
        STRAVA_CLIENT_ID,
        STRAVA_CLIENT_SECRET
    )
    print(accesor.stravaClientId, accesor.stravaClientSecret)
    strava_token = accesor.getUpdatedAccessToken(LJStravaUserID, "Strava")
    print(strava_token)


if __name__ == "__main__":
    main()
