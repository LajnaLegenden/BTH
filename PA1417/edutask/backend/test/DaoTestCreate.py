import random
import pytest
import json
from src.util.dao import DAO
from unittest.mock import patch
import pymongo
from dotenv import dotenv_values
import os
from bson.objectid import ObjectId

val = {
    "$jsonSchema": {
        "bsonType": "object",
        "required": ["string", "bool"],
        "properties": {
            "string": {
                "bsonType": "string",
                "uniqueItems": True
            },
            "bool": {
                "bsonType": "bool",
            }
        }
    }
}


def mock_getValidator(str):
    return val


class TestClass:
    @pytest.fixture(autouse=True)
    def daoSetUp(self):
        with patch("src.util.dao.getValidator") as mock_get_validator:
            mock_get_validator.return_value = val
            dao = DAO("test")
            try:
                yield dao
            finally:
                dao.drop()
    # Test db connection fails
    @patch('pymongo.MongoClient')
    def test_create_no_valid_db(self, mock_client):
        mock_client.side_effect = Exception()
        with pytest.raises(Exception):
            DAO("test")
    # Test create
    @pytest.mark.integration
    def test_create(self, daoSetUp):
        daoSetUp.create({"string": "test", "bool": True})

    # Test with duplicate
    @pytest.mark.integration
    def test_multiple_with_same_name(self, daoSetUp):
        with pytest.raises(pymongo.errors.WriteError):
            daoSetUp.create({"string": "hejsan hoppsan", "bool": True})
            daoSetUp.create({"string": "hejsan hoppsan", "bool": True})

    # Test wrong type string
    @pytest.mark.integration
    def test_wrong_types_string(self, daoSetUp):
        with pytest.raises(pymongo.errors.WriteError):
            daoSetUp.create({"string": 1, "bool": True})

    # Test wrong type bool
    @pytest.mark.integration
    def test_wrong_types_bool(self, daoSetUp):
        with pytest.raises(pymongo.errors.WriteError):
            daoSetUp.create({"string": "1", "bool": "True"})

    # test wrong names
    @pytest.mark.integration
    def test_wrong_types_bool(self, daoSetUp):
        with pytest.raises(pymongo.errors.WriteError):
            daoSetUp.create({"theString": "hejsan hoppsan", "aBool": True})
