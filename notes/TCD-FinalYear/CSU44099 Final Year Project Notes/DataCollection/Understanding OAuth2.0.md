Links: 
Tags:
___
# Understanding OAuth 2.0
Using **Third Party Authorisation** to get access to C2/Strava/etc. 
## OAuth Third Party Authorisation Process
![[Pasted image 20231107142926.png]]

In practice, the user is sent to an authorization page which then redirects to a page which handles the authorization token.
## Concept2
Uses `x-www-form-urlencoded` as body for `/oauth/access_token`. `access_token` lasts 1hr `refresh_token` lasts 1year.

___
Created: 2023-11-07

