#! /usr/bin/env python


import json
import os


DB_PATH = "restaurant.json"


class RestaurantDBError(Exception):

    pass


class RestaurantDB(object):

    _ENTITIES = ["employee", "product"]
    _REQUIRED_FIELDS = {
        "employee": [
            "name",
            "salary"
        ],
        "product": [
            "name",
            "price",
        ]
    }

    def __init__(self, db_path=DB_PATH):
        self._db_path = db_path
        self._indexes = dict.fromkeys(self._ENTITIES, 0)
        self._entities = {name: {} for name in self._ENTITIES}

        self._load()

    @classmethod
    def _check_name(cls, name):
        if name not in cls._ENTITIES:
            raise RestaurantDBError("invalid entity name {!r}".format(name))

    @classmethod
    def _check_fields(cls, name, entity):
        fields = cls._REQUIRED_FIELDS.get(name, [])
        for field in fields:
            if field not in entity:
                raise RestaurantDBError("missing field {!r} in {}: {}".format(
                    field, name, entity
                ))

    def add_entity(self, _name, entity_id=None, **kwargs):
        """Add one dict entity of its `name` kind."""
        # Check for the entity type availability and make a copy of it.
        self._check_name(_name)
        entity = kwargs.copy()
        # Now check its fields based on its type name.
        self._check_fields(_name, entity)
        # All fine, update the index.
        if entity_id:
            index = entity_id
        else:
            index = str(self._indexes[_name])
            self._indexes[_name] = int(index) + 1
        entity["id"] = index
        entity["type"] = _name
        # Finally save it.
        self._entities[_name][index] = entity
        self._save()
        return index

    def add_entities(self, name, *args):
        """Add multiple entities under the same name."""
        indexes = []
        for arg in args:
            idx = self.add_entity(name, **arg)
            indexes.append(idx)
        return indexes

    def get_entity(self, name, entity_id):
        """Retrieve one entity dict based on its ID."""
        return self._entities.get(name, {}).get(entity_id)

    def get_entities(self, name):
        """Return all the available entities IDs based on `name`."""
        return self._entities.get(name, {}).keys()

    def remove_entity(self, entity):
        """Remove a specific entity based on its type and ID."""
        name, entity_id = [entity[key] for key in ("type", "id")]
        status = bool(self.get_entity(name, entity_id=entity_id))
        if status:
            del self._entities[name][entity_id]
            self._save()
        return status

    def _load(self):
        if not os.path.isfile(self._db_path):
            return
        with open(self._db_path, "r") as stream:
            db = json.load(stream)
        self._indexes = db["indexes"]
        self._entities = db["entities"]

    def _save(self):
        db = {
            "indexes": self._indexes,
            "entities": self._entities,
        }
        with open(self._db_path, "w") as stream:
            json.dump(db, stream, indent=4, sort_keys=True)

    def drop(self, name=None):
        """Remove all records within a specified space or clear entire DB."""
        for etype, group in self._entities.items():
            if name:
                if etype == name:
                    group.clear()
                    break
            else:
                group.clear()
        self._save()


if __name__ == "__main__":
    rest = RestaurantDB()
    rest.drop()
    rest.add_entities(
        "employee",
        {
            "name": "Ion",
            "salary": "1000 EUR",
        },
        {
            "name": "Cosmin",
            "salary": "2000 RON",
            "age": "23"
        }
    )
    rest.add_entities(
        "product",
        {
            "name": "Salata",
            "price": "16 RON",
        },
        {
            "name": "Gratar pui",
            "price": "19 RON",
            "kcal": "400",
        }
    )
    print("Initialized database.")
