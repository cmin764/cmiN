from datetime import datetime
from enum import Enum
from typing import Annotated, Literal

import httpx
from fastapi import FastAPI, Query, APIRouter  # , Request
# from fastapi.exceptions import RequestValidationError
# from fastapi.responses import JSONResponse
from pydantic import BaseModel, Field, HttpUrl


# from starlette.status import HTTP_400_BAD_REQUEST


class ModelName(str, Enum):
    alexnet = "alexnet"
    resnet = "resnet"
    lenet = "lenet"


class Item(BaseModel):
    name: str
    description: str | None = None
    price: float
    tax: float | None = None


class FilterParams(BaseModel):
    limit: Annotated[int, Field(gt=0, le=100)] = 100
    offset: Annotated[int | None, Field(ge=0)] = 0
    order_by: Literal["created_at", "updated_at"] = "created_at"
    tags: list[str] = []


app = FastAPI()


# @app.exception_handler(RequestValidationError)
# async def custom_validation_exception_handler(
#     _: Request, exc: RequestValidationError
# ):
#     return JSONResponse(
#         status_code=HTTP_400_BAD_REQUEST,
#         content={"detail": exc.errors(), "body": exc.body},
#     )


@app.get("/")
async def root():
    return {"message": "Hello World"}


@app.get("/items/{item_id}")
async def read_item(item_id: int):
    return {"item_id": item_id}


@app.post("/items/")
async def create_item(item: Item):
    print(item.price)
    return item


@app.get("/items/")
async def read_items(q: Annotated[list[str], Query()] = ["foo", "bar"]):
    results: dict[str, list[dict[str, str]] | list[str]] = {
        "items": [{"item_id": "Foo"}, {"item_id": "Bar"}]
    }
    if q:
        q.append("rick")
        results.update({"q": q})
    return results


@app.get("/my_items/", response_model=FilterParams, response_model_exclude_unset=True)
async def read_my_items(filter_query: Annotated[FilterParams, Query()]):
    return filter_query
    # return {"tags": ["a", "b"]}


@app.get("/users/me")
async def read_user_me():
    return {"user_id": "the current user"}


@app.get("/users/{user_id}")
async def read_user(user_id: str, offset: int = 0):
    return {"user_id": user_id}


@app.get("/models/{model_name}")
async def get_model(model_name: ModelName):
    if model_name is ModelName.alexnet:
        return {"model_name": model_name, "message": "Deep Learning FTW!"}

    if model_name.value == "lenet":
        return {"model_name": model_name, "message": "LeCNN all the images"}

    return {"model_name": model_name, "message": "Have some residuals"}


@app.get("/files/{file_path:path}")
async def read_file(file_path: str):
    with open(file_path) as stream:
        data = stream.read()
    return {"file_path": file_path, "content": data}


items = {
    "foo": {"name": "Foo", "price": 50.2},
    "bar": {"name": "Bar", "description": "The Bar fighters", "price": 62, "tax": 20.2},
    "baz": {
        "name": "Baz",
        "description": "There goes my baz",
        "price": 50.2,
        "tax": 10.5,
    },
}


@app.get(
    "/items/{item_id}/name",
    response_model=Item,
    response_model_include={"name", "description"},  # include only
)
async def read_item_name(item_id: str):
    return items[item_id]


@app.get("/items/{item_id}/public", response_model=Item, response_model_exclude={"tax"})
async def read_item_public_data(item_id: str):
    return items[item_id]


class Invoice(BaseModel):
    id: str
    title: str | None = None
    customer: str
    total: float


class InvoiceEvent(BaseModel):
    description: str
    paid: bool


class InvoiceEventReceived(BaseModel):
    ok: bool


invoices_callback_router = APIRouter()


@invoices_callback_router.post(
    "{$callback_url}/invoices/{$request.body.id}", response_model=InvoiceEventReceived
)
async def invoice_notification(body: InvoiceEvent):
    pass


@invoices_callback_router.post(
    "/invoices/{invoice_id}", response_model=InvoiceEventReceived
)
async def invoice_notification_route(invoice_id: str, body: InvoiceEvent):
    print(invoice_id, body.model_dump())
    return {"ok": True}


app.mount("/callbacks", invoices_callback_router)


@app.post("/invoices/", callbacks=invoices_callback_router.routes)
async def create_invoice(invoice: Invoice, callback_url: HttpUrl | None = None):
    """
    Create an invoice.

    This will (let's imagine) let the API user (some external developer) create an
    invoice.

    And this path operation will:

    * Send the invoice to the client.
    * Collect the money from the client.
    * Send a notification back to the API user (the external developer), as a callback.
        * At this point is that the API will somehow send a POST request to the
            external API with the notification of the invoice event
            (e.g. "payment successful").
    """
    # Send the invoice, collect the money, send the notification (the callback)
    if callback_url:
        callback_event = InvoiceEvent(
            description=f"Invoice {invoice.id} payment successful",
            paid=True,
        )
        callback_full_url = f"{callback_url}/invoices/{invoice.id}"

        async with httpx.AsyncClient() as client:
            response = await client.post(
                callback_full_url, json=callback_event.model_dump()
            )
            if response.status_code == 200:
                return {"msg": "Invoice received and callback sent"}
            else:
                return {
                    "msg": "Invoice received but callback failed",
                    "callback_status": response.status_code,
                }

    return {"msg": "Invoice received"}


class Subscription(BaseModel):
    username: str
    monthly_fee: float
    start_date: datetime


@app.webhooks.post("new-subscription")
def new_subscription(body: Subscription):
    """
    When a new user subscribes to your service we'll send you a POST request with this
    data to the URL that you register for the event `new-subscription` in the dashboard.
    """
