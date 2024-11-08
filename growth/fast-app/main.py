from enum import Enum
from typing import Annotated, Literal

from fastapi import FastAPI, Query  # , Request
# from fastapi.exceptions import RequestValidationError
# from fastapi.responses import JSONResponse
from pydantic import BaseModel, Field


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
    offset: Annotated[int, Field(ge=0)] = 0
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


@app.get("/my_items/")
async def read_my_items(filter_query: Annotated[FilterParams, Query(deprecated=True)]):
    return filter_query


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
