#! /usr/bin/env python


import BaseHTTPServer
import json
import re
import threading
import unittest

import requests

import rdb
import rserver


DB_PATH = "test_restaurant.json"


class TestRestaurantDB(unittest.TestCase):

    def setUp(self):
        self.db = rdb.RestaurantDB(DB_PATH)
        self.db.drop()

    def test_entity(self):
        eid = self.db.add_entity(
            "product",
            name="Pizza",
            price="20 RON",
        )
        pizza = self.db.get_entity("product", eid)
        pizza["price"] = "22 RON"
        eid2 = self.db.add_entity(
            "product",
            entity_id=eid,
            **pizza
        )
        pizza2 = self.db.get_entity("product", eid2)
        self.assertEqual(eid, eid2)
        self.assertEqual(pizza, pizza2)
        self.db.remove_entity(pizza)
        pizza2 = self.db.get_entity("product", eid2)
        self.assertFalse(pizza2)


class TestRESTHanlder(unittest.TestCase):

    HEADERS = {
        "Content-type": "application/json",
        "Content-Length": None,
    }

    def _serve(self):
        try:
            self.httpd.serve_forever()
        except Exception:
            pass

    def setUp(self):
        rserver.RESTHandler.DB_PATH = DB_PATH
        self.httpd = BaseHTTPServer.HTTPServer(
            (rserver.HOST, rserver.PORT),
            rserver.RESTHandler
        )
        self.thread = threading.Thread(target=self._serve)
        self.thread.start()

    def tearDown(self):
        self.httpd.server_close()
        self.thread.join()
        rdb.RestaurantDB(DB_PATH).drop()

    @classmethod
    def _api_call(cls, url, data=None, force_method=None):
        headers = cls.HEADERS.copy()
        payload = json.dumps(data) if data else None
        if payload:
            headers.update({
                "Content-Length": str(len(payload)),
            })
        if data:
            method = requests.post
        else:
            method = requests.get
        method = force_method or method
        response = method(url, headers=headers, data=payload)
        response.raise_for_status()
        if method in (requests.head, requests.delete):
            return response.text
        return response.json()["result"]

    def test_products(self):
        # Initial data.
        url = "http://{}:{}/products".format(rserver.HOST, rserver.PORT)
        data = {
            "name": "Pizza",
            "price": "20 RON",
        }
        # Add product.
        product_url = self._api_call(url, data=data)["product"]
        self.assertRegexpMatches(product_url, r"{}/\d+".format(url))
        # Retrieve all product URLs.
        product_urls = self._api_call(url)["products"]
        self.assertEqual(product_url, product_urls[0])
        # Retrieve product details.
        product = self._api_call(product_url)["product"]
        product.pop("id")
        product.pop("type")
        self.assertDictEqual(data, product)
        # Modify product.
        new_data = data.copy()
        new_data.update({
            "price": "22 RON",
        })
        new_product_url = self._api_call(
            product_url, data=new_data,
            force_method=requests.put
        )["product"]
        self.assertEqual(product_url, new_product_url)
        new_product = self._api_call(new_product_url)["product"]
        self.assertEqual("22 RON", new_product["price"])
        # Remove product (empty products list).
        self._api_call(new_product_url, force_method=requests.delete)
        with self.assertRaisesRegexp(
                requests.HTTPError, re.compile(r"404.+?Not Found")):
            product = self._api_call(new_product_url)["product"]
        product_urls = self._api_call(url)["products"]
        self.assertFalse(product_urls)

    def test_employees(self):
        # Initial data.
        url = "http://{}:{}/employees".format(rserver.HOST, rserver.PORT)
        data = {
            "name": "Cosmin",
            "salary": "3000 EUR",
        }
        # Add employee.
        employee_url = self._api_call(url, data=data)["employee"]
        self.assertRegexpMatches(employee_url, r"{}/\d+".format(url))
        # Retrieve all employee URLs.
        employee_urls = self._api_call(url)["employees"]
        self.assertEqual(employee_url, employee_urls[0])
        # Retrieve employee details.
        employee = self._api_call(employee_url)["employee"]
        employee.pop("id")
        employee.pop("type")
        self.assertDictEqual(data, employee)
        # Modify employee.
        new_data = data.copy()
        new_data.update({
            "price": "22 RON",
        })
        new_employee_url = self._api_call(
            employee_url, data=new_data,
            force_method=requests.put
        )["employee"]
        self.assertEqual(employee_url, new_employee_url)
        new_employee = self._api_call(new_employee_url)["employee"]
        self.assertEqual("22 RON", new_employee["price"])
        # Remove employee (empty employees list).
        self._api_call(new_employee_url, force_method=requests.delete)
        with self.assertRaisesRegexp(
                requests.HTTPError, re.compile(r"404.+?Not Found")):
            employee = self._api_call(new_employee_url)["employee"]
        employee_urls = self._api_call(url)["employees"]
        self.assertFalse(employee_urls)


if __name__ == "__main__":
    unittest.main()
