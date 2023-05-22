from unittest.mock import patch
import pytest
import os
import json
from src.controllers.receipecontroller import ReceipeController
# import Diet
from src.static.diets import Diet, from_string
# add your test case implementation here

# fixture to load all receipes


def load_receipes():
    """Read all available receipes from the src/static/receipes/ directory and puts them in an array. The items of this array follow the same format as the JSON files in the directory.

    returns:
      receipes -- list of receipes in dictionary format"""
    receipes: list[dict] = []
    for filename in os.listdir('./src/static/receipes'):
        with open(f'./src/static/receipes/{filename}') as f:
            receipe = json.load(f)
            receipes.append(receipe)
    return receipes


@pytest.mark.unit
def test_100_readiness():
    avalible = {
        "Butter": 100,
        "Banana": 4,
        "Sugar": 200,
        "Egg": 1,
        "Vanilla Sugar": 1,
        "Baking Powder": 0.5,
        "Salt": 5,
        "Cinnamon": 10,
        "Flour": 220,
        "Walnuts": 10
    }
    c = ReceipeController(items_dao=None)
    result = c.get_receipe_readiness(receipe=load_receipes(
    )[0], available_items=avalible, diet=from_string("vegetarian"))
    assert result == 1


@pytest.mark.unit
def test_invalid_diet_for_recepie():
    avalible = {
        "Butter": 100,
        "Banana": 4,
        "Sugar": 200,
        "Egg": 1,
        "Vanilla Sugar": 1,
        "Baking Powder": 0.5,
        "Salt": 5,
        "Cinnamon": 10,
        "Flour": 220,
        "Walnuts": 10
    }
    c = ReceipeController(items_dao=None)
    result = c.get_receipe_readiness(receipe=load_receipes(
    )[0], available_items=avalible, diet=from_string("vegan"))
    assert result == None


@pytest.mark.unit
def test_some_ingredients():
    avalible = {
        "Butter": 50,
        "Banana": 2,
        "Sugar": 50,
        "Egg": 1,
        "Vanilla Sugar": 1,
        "Baking Powder": 0.5,
        "Salt": 5,
        "Cinnamon": 10,
        "Flour": 220,
        "Walnuts": 10
    }
    c = ReceipeController(items_dao=None)
    result = c.get_receipe_readiness(receipe=load_receipes(
    )[0], available_items=avalible, diet=from_string("vegetarian"))
    assert result > 0.1
    assert result < 1

# test that mocks returnvalue from src.util.calculator


@pytest.mark.unit
def test_some_ingredients_no_diet():

    avalible = {
        "Butter": 50,
        "Banana": 2,
        "Sugar": 50,
        "Egg": 1,
        "Vanilla Sugar": 1,
        "Baking Powder": 0.5,
        "Salt": 5,
        "Cinnamon": 10,
        "Flour": 220,
        "Walnuts": 10
    }
    c = ReceipeController(items_dao=None)
    result = c.get_receipe_readiness(receipe=load_receipes(
    )[0], available_items=avalible, diet=from_string("vegetarian"))
    assert 0.1 < result < 1


@pytest.mark.unit
def test_no_ingredients_valid_diet():

    avalible = {}
    c = ReceipeController(items_dao=None)
    result = c.get_receipe_readiness(receipe=load_receipes(
    )[0], available_items=avalible, diet=from_string("vegetarian"))
    assert result == None


@pytest.mark.unit
def test_no_ingredients_invalid_diet():

    avalible = {}
    c = ReceipeController(items_dao=None)
    result = c.get_receipe_readiness(receipe=load_receipes(
    )[0], available_items=avalible, diet=from_string("vegan"))
    assert result == None


@pytest.mark.unit
def test_invalid_recepie():

    avalible = {}
    c = ReceipeController(items_dao=None)
    recepie = {
        "name": "Pancakes",
        "diets": [
        ],
        "ingredients": {

        }
    }
    result = c.get_receipe_readiness(
        receipe=recepie, available_items=avalible, diet=from_string("vegan"))
    assert result == None
