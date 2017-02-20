#! /usr/bin/env python


import json
import re
import textwrap
import sys

import requests


EMAILS_PATH = "hello_emails.txt"


class Hello(object):

    API_KEYS = {
        "sendgrid": ("SG.GK11lH6ZRTy8zngPga_EcA."
                     "BDvomiS7kRHo0j_xt_JWahm81ZNsqcvhqoDt5UFuBXg"),
        "location": "AIzaSyAodrxR9w1AqmdajcrrRqFTnNXsyE2mwaM",
        "weather": "db310acfbeeb7a7697f13bb18c43a073"
    }

    LOCATION_INDEX = 1    # in the returned list of results

    def __init__(self, from_email, to_emails_path):
        """Instantiate with the from `email` address."""
        self._from_email = from_email
        self._to_emails = self.load_emails(to_emails_path)

    def get_location(self):
        # Get coordinates.
        url = "https://www.googleapis.com/geolocation/v1/geolocate?key={}"
        url = url.format(self.API_KEYS["location"])
        response = requests.post(url)
        response.raise_for_status()
        result = response.json()["location"]
        lat, lon = map(lambda key: result[key], ("lat", "lng"))

        # Now reverse geocoding to location/address.
        url = ("http://maps.googleapis.com/maps/api/geocode/json?"
               "latlng={},{}&sensor=false").format(lat, lon)
        response = requests.get(url)
        response.raise_for_status()
        result = response.json()
        address = result["results"][self.LOCATION_INDEX]["formatted_address"]
        location = address.split(",")[1].strip()
        return location

    def get_weather(self, location):
        url = ("http://api.openweathermap.org/data/2.5/"
               "weather?q={input}&appid={key}").format(
            input=location,
            key=self.API_KEYS["weather"]
        )
        response = requests.get(url)
        response.raise_for_status()
        result = response.json()["weather"][0]
        weather = "{} - {}".format(result["main"], result["description"])
        return weather

    @staticmethod
    def load_emails(path):
        emails = []
        with open(path) as stream:
            for line in stream:
                idx = line.find("#")
                if idx:
                    line = line[:idx]
                line = line.strip()
                if not line:
                    continue
                emails.append(line)
        return emails

    def send_mail(self, subject, text):
        url = "https://api.sendgrid.com/v3/mail/send"
        headers = {
            "Authorization": "Bearer {}".format(self.API_KEYS["sendgrid"]),
            "Content-Type": "application/json",
        }
        data = {
            "personalizations": [
                {
                    "to": [
                        {
                            "email": None,
                            "name": "Happy User"
                        }
                    ],
                    "subject": None,
                }
            ],
            "from": {
                "email": None,
                "name": "FII Cloud"
            },
            "subject": None,
            "content": [
                {
                    "type": "text/html",
                    "value": None
                }
            ],
            "tracking_settings": {
                "click_tracking": {
                    "enable": True,
                    "enable_text": True
                },
                "open_tracking": {
                    "enable": True,
                    "substitution_tag": "%opentrack"
                },
            }
        }

        data["from"]["email"] = self._from_email
        data["subject"] = subject
        data["content"][0]["value"] = text
        data["personalizations"][0]["subject"] = subject
        items = [{"email": email, "name": "Happy User"}
                 for email in self._to_emails]
        data["personalizations"][0]["to"] = items

        payload = json.dumps(data, separators=(",", ":"))
        response = requests.post(url, headers=headers, data=payload)
        response.raise_for_status()

    def start(self):
        location = self.get_location()
        weather = self.get_weather(location)

        subject = "Hi from {}".format(location)
        text = textwrap.dedent("""
        Hi there,

        I'm from {} and the weather outside is:
        {}
        """.format(location, weather))
        self.send_mail(subject, text)


def main():
    if len(sys.argv) != 2:
        print("Usage: {} EMAIL".format(sys.argv[0]))
        return 1

    try:
        hello = Hello(sys.argv[1], EMAILS_PATH)
        hello.start()
    except Exception as exc:
        print("Error occurred: {}.".format(exc))
        return 2

    print("Success run.")
    return 0


if __name__ == "__main__":
    code = main()
    sys.exit(code)
