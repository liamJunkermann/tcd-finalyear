from requests import request
import time


class StravaApi:
    access_token = ""

    def __init__(self, access_token: str):
        self.access_token = access_token

    def getStravaUserActivity(self, activity_id):
        url = "https://www.strava.com/api/v3/activites/"+activity_id
        headers = {
            'accept': 'application/json',
            'Authorization': 'Bearer ' + self.access_token
        }

        response = request("GET", url, headers=headers)
        return response

    def getStravaUserActivities(self, before=int(time.time()), after=0, per_page=100, page=1):
        url = "https://www.strava.com/api/v3/athlete/activities?before=" + \
            str(before)+"&after="+str(after)+"&per_page=" + \
            str(per_page)+"&page="+str(page)
        # url = "https://www.strava.com/api/v3/athlete/activities?before=1709568657&after=0&page=1&per_page=100"
        headers = {
            'accept': 'application/json',
            'Authorization': 'Bearer ' + self.access_token
        }

        response = request("GET", url, headers=headers)
        return response
