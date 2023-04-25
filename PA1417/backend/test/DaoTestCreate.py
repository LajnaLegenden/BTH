import random
import pytest
import json
from src.util.dao import DAO
from unittest.mock import patch
import pymongo
from dotenv import dotenv_values
import os
from bson.objectid import ObjectId

def mock_getValidator(str):
    print (f"Mocking getValidator for {str}")
    key = str.split(":")[1]
    print (f"Schema is {key}")
    with open(f'./src/static/validators/{key}.json', 'r') as f:
        return json.load(f)
      

class TestClass:
    usedIds = {}
    prefix = "test_"
    @classmethod
    def setup_class(self):
        # Set up code before the class of tests
        print("Before all tests")
        self.usedIds = {
            "user": [],
            "task": [],
            "video": [],
            "todo": []
        }
        self.prefix = self.prefix + self.get_random_string(self,10) + ":"
        
    #util class
    def get_random_string(self, length):
        letters = "abcdefghijklmnopqrstuvwxyz"
        result_str = ''.join(random.choice(letters) for i in range(length))
        return result_str

    @classmethod
    def teardown_class(self):
        print("After all tests")
                # load the local mongo URL (something like mongodb://localhost:27017)
        LOCAL_MONGO_URL = dotenv_values('.env').get('MONGO_URL')
        # check out of the environment (which can be overridden by the docker-compose file) also specifies an URL, and use that instead if it exists
        MONGO_URL = os.environ.get('MONGO_URL', LOCAL_MONGO_URL)

        client = pymongo.MongoClient(MONGO_URL)
        database = client.edutask
        # Tear down code after the class of tests
        # Delete all the created objects
        for key in self.usedIds:
            dao = DAO(self.prefix +key)
            for id in self.usedIds[key]:
                print(f"Deleting {key} with id {id}")
                dao.delete(id['$oid'])
            # Delete the collections
            print(f"Dropping collection {self.prefix + key}")
            database.drop_collection(self.prefix + key)

        


#############################################
# USER TESTS
#############################################
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_user(self, capsys, monkeypatch):
            dao = DAO(self.prefix + "user")
            user = dao.create({"firstName": "John1","lastName": "Doe", "email": f"{self.get_random_string(10)}@gmail.com", "tasks": []})
            self.usedIds["user"].append(user["_id"])
            foundUser = dao.find({"firstName": "John1"})
            assert foundUser[0]["email"] == user["email"]
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_user_no_email(self, monkeypatch):
        dao = DAO(self.prefix + "user")
        with pytest.raises(Exception):
            dao.create({"firstName": "John","lastName": "Doe",  "tasks": []})
    
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_user_no_firstName(self, monkeypatch):
        dao = DAO(self.prefix + "user")
        with pytest.raises(Exception):
            dao.create({"lastName": "Doe", "email": f"{self.get_random_string(10)}@gmail.com", "tasks": []})
    
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_user_no_lastName(self, monkeypatch):
        dao = DAO(self.prefix + "user")
        with pytest.raises(Exception):
            dao.create({"firstName": "John", "email": f"{self.get_random_string(10)}@gmail.com", "tasks": []})
    
    #create user works with no tasks
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_user_no_tasks(self,monkeypatch):
        dao = DAO(self.prefix + "user")
        user = dao.create({"firstName": "John2","lastName": "Doe", "email": f"{self.get_random_string(10)}@gmail.com"})
        self.usedIds["user"].append(user["_id"])
        foundUser = dao.find({"firstName": "John2"})
        assert foundUser[0]["email"] == user["email"]

    #test if email is array
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_user_email_array(self, monkeypatch):
        dao = DAO(self.prefix + "user")
        with pytest.raises(Exception):
            dao.create({"firstName": "John","lastName": "Doe", "email": []})

#############################################
# TODO TESTS
#############################################

    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_todo(self, monkeypatch):
        dao = DAO(self.prefix + "todo")
        todo = dao.create({"description": self.get_random_string(10), "completed": False})
        self.usedIds["todo"].append(todo["_id"])
        foundTodo = dao.find({"description": todo["description"]})
        assert foundTodo[0]["description"] == todo["description"]
    
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_todo_no_description(self,monkeypatch):
        dao = DAO(self.prefix + "todo")
        with pytest.raises(Exception):
            dao.create({"completed": False})
        
    #should be able to create a todo with no completed field
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_todo_no_completed(self,monkeypatch):
        dao = DAO(self.prefix + "todo")
        todo = dao.create({"description": self.get_random_string(10)})
        self.usedIds["todo"].append(todo["_id"])
        foundTodo = dao.find({"description": todo["description"]})
        assert foundTodo[0]["description"] == todo["description"]
    
    #wrong type for completed
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_todo_completed_wrong_type(self,monkeypatch):
        dao = DAO(self.prefix + "todo")
        with pytest.raises(Exception):
            dao.create({"description": self.get_random_string(10), "done": "falsk"})

#############################################
# VIDEO TESTS
#############################################

    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_video(self,monkeypatch):
        dao = DAO(self.prefix + "video")
        video = dao.create({"url": f"https://www.youtube.com/watch?v={self.get_random_string(8)}"})
        self.usedIds["video"].append(video["_id"])
        foundVideo = dao.find({"url": video["url"]})
        assert foundVideo[0]["url"] == video["url"]
    
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_video_no_url(self,monkeypatch):
        dao = DAO(self.prefix + "video")
        with pytest.raises(Exception):
            dao.create({})
    
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_video_url_array(self,monkeypatch):
        dao = DAO(self.prefix + "video")
        with pytest.raises(Exception):
            dao.create({"url": []})

#############################################
# TASK TESTS
#############################################

    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_task(self,monkeypatch):
        dao = DAO(self.prefix + "task")
        task = dao.create({"title": "Task1", "description": "This is a task", "todos": []})
        self.usedIds["task"].append(task["_id"])
        foundTask = dao.find({"title": task["title"]})
        assert foundTask[0]["title"] == task["title"]
    
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_task_no_title(self,monkeypatch):
        dao = DAO(self.prefix + "task")
        with pytest.raises(Exception):
            dao.create({"description": "This is a task", "todos": []})
    
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_task_no_description(self,monkeypatch):
        dao = DAO(self.prefix + "task")
        with pytest.raises(Exception):
            dao.create({"title": "Task1", "todos": []})
    
    #allows start and due dates
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_task_with_dates(self,monkeypatch):
        dao = DAO(self.prefix + "task")
        task = dao.create({"title": "Task1", "description": "This is a task", "todos": [], "startDate": "2020-10-10", "dueDate": "2020-10-10"})
        self.usedIds["task"].append(task["_id"])
        foundTask = dao.find({"title": task["title"]})
        assert foundTask[0]["title"] == task["title"]

    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_task_with_categories(self,monkeypatch):
        dao = DAO(self.prefix + "task")
        task = dao.create({"title": "Task1", "description": "This is a task", "todos": [],  "categories": ["category1", "category2"]})
        self.usedIds["task"].append(task["_id"])
        foundTask = dao.find({"title": task["title"]})
        assert foundTask[0]["title"] == task["title"]
    
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_invalid_task_categories_string(self,monkeypatch):
        dao = DAO(self.prefix + "task")
        with pytest.raises(Exception):
            dao.create({"title": "Task2", "description": "This is a task", "todos": [], "video": [], "categories": "category1"})
        
    @patch('src.util.dao.getValidator', side_effect=mock_getValidator)
    def test_create_task_with_todos_and_videos(self,monkeypatch):
        dao = DAO(self.prefix + "task")
        todoDao = DAO(self.prefix + "todo")
        videoDao = DAO(self.prefix + "video")
        todo = todoDao.create({"description": "This is a todo", "done": False})
        video = videoDao.create({"url": f"https://www.youtube.com/watch?v={self.get_random_string(8)}"})
        self.usedIds["todo"].append(todo["_id"])
        self.usedIds["video"].append(video["_id"])
        task = dao.create({"title": "Task3", "description": "This is a task", "todos": [ObjectId(todo["_id"]['$oid'])], "video":ObjectId(video["_id"]['$oid'])})
        self.usedIds["task"].append(task["_id"])
        foundTask = dao.find({"title": task["title"]})
        assert foundTask[0]["title"] == task["title"]
    