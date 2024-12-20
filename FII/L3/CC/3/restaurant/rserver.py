#! /usr/bin/env python


import BaseHTTPServer
import json
import re
import urlparse

import rdb


HOST = "127.0.0.1"
PORT = 8080


class ResponseError(Exception):

    def __init__(self, code, message, *args, **kwargs):
        super(ResponseError, self).__init__(*args, **kwargs)
        self.code = code
        self.message = message


class Request(object):

    def __init__(self, method, path, data):
        self._method = method
        self.path = path
        self.data = data

    @property
    def HEAD(self):
        return "HEAD" == self._method

    @property
    def POST(self):
        return "POST" == self._method

    @property
    def GET(self):
        return "GET" == self._method

    @property
    def PUT(self):
        return "PUT" == self._method

    @property
    def DELETE(self):
        return "DELETE" == self._method


class URIBuilder(object):

    SCHEME = "http"

    def __init__(self, handler):
        self._handler = handler

    def uri(self, entity_id):
        address = self._handler.server.server_address
        path = re.match(r"/\w+", self._handler.path).group() + "/"
        path = urlparse.urljoin(path, entity_id)
        uri = urlparse.urlunsplit((
            self.SCHEME,
            "{}:{}".format(*address),
            path,
            "",
            ""
        ))
        return uri


class RESTHandler(BaseHTTPServer.BaseHTTPRequestHandler):

    ROUTES = {}
    DB_PATH = "restaurant.json"

    def __init__(self, *args, **kwargs):
        self.db = rdb.RestaurantDB(self.DB_PATH)
        # NOTE(cmiN): do not write anything after this line (blocking).
        BaseHTTPServer.BaseHTTPRequestHandler.__init__(self, *args, **kwargs)

    @classmethod
    def route(cls, route_path):
        def router(func):
            cls.ROUTES[route_path] = func
            return func
        return router

    def get_payload(self):
        payload_len = int(self.headers.getheader("Content-Length", 0))
        payload = self.rfile.read(payload_len).strip()
        if not payload:
            return None
        return json.loads(payload)

    def send_result(self, result, code=200):
        payload = json.dumps(
            {
                "status": "ok",
                "result": result,
            },
            indent=4,
        )
        length = len(payload)

        self.send_response(code)
        self.send_header("Content-Type", "application/json")
        if result is not None:
            self.send_header("Content-Length", str(length))
        self.end_headers()
        if result is not None:
            self.wfile.write(payload + "\n")

    def do_HEAD(self):
        self.handle_method('HEAD')

    def do_POST(self):
        self.handle_method('POST')

    def do_GET(self):
        self.handle_method('GET')

    def do_PUT(self):
        self.handle_method('PUT')

    def do_DELETE(self):
        self.handle_method('DELETE')

    def _get_handle_function(self):
        for regex, func in self.ROUTES.items():
            match = re.match(r"^{}$".format(regex), self.path)
            if match:
                return func, match.groups()
        raise ResponseError(404, "Not Found")

    def _get_request(self, method):
        return Request(method, self.path, self.get_payload())

    def _get_code(self, request):
        status = {
            request.HEAD: 200,
            request.POST: 201,
            request.GET: 200,
            request.PUT: 201,
            request.DELETE: 204,
        }
        return status.get(True, 200)

    def handle_method(self, method):
        try:
            handle_function, extra = self._get_handle_function()
            request = self._get_request(method)
            result = handle_function(self, request, *extra)
        except ResponseError as exc:
            self.send_response(exc.code)
            self.end_headers()
            self.wfile.write(exc.message + "\n")
        except Exception as exc:
            self.send_response(500)
            self.end_headers()
            self.wfile.write("Internal Server Error: {}\n".format(exc))
            # FIXME(cmiN): remove this after debugging
            raise
        else:
            code = self._get_code(request)
            self.send_result(result, code=code)


route = RESTHandler.route


@route(r"/")
def handle_home(handler, request):
    if request.GET:
        return {
            "help": {
                "/products": {
                    "POST": "Add new product with mandatory fields.",
                    "GET": "Retrieve a list of all available products.",
                    "DELETE": "Remove all available products",
                },
                "/products/<ID>": {
                    "GET": "Retrieve specified product's details.",
                    "PUT": "Update current product with provided details.",
                    "DELETE": "Remove the specified product.",
                },
                "/employees": {
                    "POST": "Add new employee with mandatory fields.",
                    "GET": "Retrieve a list of all available employees.",
                    "DELETE": "Remove all available employees",
                },
                "/employees/<ID>": {
                    "GET": "Retrieve specified employee's details.",
                    "PUT": "Update current employee with provided details.",
                    "DELETE": "Remove the specified employee.",
                },
            }
        }
    if request.HEAD:
        return None
    raise ResponseError(405, "Method Not Allowed")


@route(r"/products")
def handle_products(handler, request):
    ubuild = URIBuilder(handler)
    if request.POST:
        try:
            data = request.data or {}
            product_id = handler.db.add_entity("product", **data)
        except rdb.RestaurantDBError as exc:
            raise ResponseError(400, str(exc))
        return {
            "product": ubuild.uri(product_id),
        }
    elif request.GET:
        return {
            "products": map(ubuild.uri, handler.db.get_entities("product")),
        }
    elif request.DELETE:
        handler.db.drop(name="product")
        return None
    # Method not allowed here.
    raise ResponseError(405, "Method Not Allowed")


@route(r"/products/(\d+)")
def handle_product(handler, request, product_id):
    get_product = lambda: handler.db.get_entity("product", product_id)
    ubuild = URIBuilder(handler)
    if request.GET:
        product = get_product()
        if product is None:
            raise ResponseError(404, "Not Found")
        return {
            "product": product,
        }
    elif request.PUT:
        entity_id = None
        product = get_product()
        if product:
            entity_id = product_id
        try:
            data = request.data or {}
            product_id = handler.db.add_entity(
                "product", entity_id=entity_id, **data)
        except rdb.RestaurantDBError as exc:
            raise ResponseError(400, str(exc))
        return {
            "product": ubuild.uri(product_id),
        }
    elif request.DELETE:
        product = get_product()
        if product is None:
            raise ResponseError(404, "Not Found")
        handler.db.remove_entity(product)
        return None
    raise ResponseError(405, "Method Not Allowed")


@route(r"/employees")
def handle_employees(handler, request):
    ubuild = URIBuilder(handler)
    if request.POST:
        try:
            data = request.data or {}
            employee_id = handler.db.add_entity("employee", **data)
        except rdb.RestaurantDBError as exc:
            raise ResponseError(400, str(exc))
        return {
            "employee": ubuild.uri(employee_id),
        }
    elif request.GET:
        return {
            "employees": map(ubuild.uri, handler.db.get_entities("employee")),
        }
    elif request.DELETE:
        handler.db.drop(name="employee")
        return None
    # Method not allowed here.
    raise ResponseError(405, "Method Not Allowed")


@route(r"/employees/(\d+)")
def handle_employee(handler, request, employee_id):
    get_employee = lambda: handler.db.get_entity("employee", employee_id)
    ubuild = URIBuilder(handler)
    if request.GET:
        employee = get_employee()
        if employee is None:
            raise ResponseError(404, "Not Found")
        return {
            "employee": employee,
        }
    elif request.PUT:
        entity_id = None
        employee = get_employee()
        if employee:
            entity_id = employee_id
        try:
            data = request.data or {}
            employee_id = handler.db.add_entity(
                "employee", entity_id=entity_id, **data)
        except rdb.RestaurantDBError as exc:
            raise ResponseError(400, str(exc))
        return {
            "employee": ubuild.uri(employee_id),
        }
    elif request.DELETE:
        employee = get_employee()
        if employee is None:
            raise ResponseError(404, "Not Found")
        handler.db.remove_entity(employee)
        return None
    raise ResponseError(405, "Method Not Allowed")


def main():
    httpd = BaseHTTPServer.HTTPServer(
        (HOST, PORT),
        RESTHandler
    )
    print("Starting server at {}:{}...".format(HOST, PORT))
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    print("Stopping server.")
    httpd.server_close()


if __name__ == "__main__":
    main()
