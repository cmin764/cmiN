#! /usr/bin/env python


import json
import re
import textwrap
import sys

import requests
from cryptography.fernet import Fernet


EMAILS_PATH = "hello_emails.txt"
API_KEYS_PATH = "api_keys.json"


def is_ascii(string):
    return all(ord(char) < 128 for char in string)


class Hello(object):

    def __init__(self, from_email,
                 to_emails_path=EMAILS_PATH, api_keys_path=API_KEYS_PATH):
        """Instantiate with the from `email` address."""
        self._from_email = from_email
        self._to_emails = self.load_emails(to_emails_path)
        self._api_keys = self.load_api_keys(api_keys_path)

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

    @staticmethod
    def load_api_keys(path):
        with open(path) as stream:
            api_keys = json.load(stream)
        key = api_keys.pop("key")
        fernet = Fernet(key.encode())
        for key, value in list(api_keys.items()):
            api_keys[key] = fernet.decrypt(value.encode())
        return api_keys

    def get_location(self):
        # Get coordinates.
        url = "https://www.googleapis.com/geolocation/v1/geolocate?key={}"
        url = url.format(self._api_keys["location"])
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

        location = None
        for address_chunks in result["results"][4:]:
            address = address_chunks["formatted_address"]
            location = address.split(",")[0].strip()
            if is_ascii(location):
                break
        return location

    def get_weather(self, location):
        url = ("http://api.openweathermap.org/data/2.5/"
               "weather?q={input}&appid={key}")
        url = url.format(
            input=location,
            key=self._api_keys["weather"]
        )
        response = requests.get(url)
        response.raise_for_status()
        result = response.json()["weather"][0]
        weather = "{} - {}".format(result["main"], result["description"])
        return weather

    def send_mail(self, subject, text):
        url = "https://api.sendgrid.com/v3/mail/send"
        headers = {
            "Authorization": "Bearer {}".format(self._api_keys["sendgrid"]),
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
        hello = Hello(sys.argv[1])
        hello.start()
    except Exception as exc:
        print("Error occurred: {}.".format(exc))
        return 2

    print("Success run.")
    return 0


if __name__ == "__main__":
    code = main()
    sys.exit(code)
