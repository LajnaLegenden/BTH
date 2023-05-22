import pytest
from userDaoMock import MockDao
from src.controllers.usercontroller import UserController
@pytest.mark.unit
def test_get_user_by_email_value_error():
    uc = UserController(dao=None)
    with pytest.raises(ValueError):
        uc.get_user_by_email(email='jane.doe')
@pytest.mark.unit
def test_get_user_by_email_with_real_email():
    uc = UserController(dao=None)
    with pytest.raises(Exception) as e:
        uc.get_user_by_email(
            email='jane.doe@gmail.com')
    assert not isinstance(e.value, ValueError)

@pytest.mark.unit
def test_get_user_by_email_with_valid_email():
    mockDb = MockDao()
    uc = UserController(dao=mockDb)
    user = {'firstName': 'Jane', 'lastName': 'Doe', 'email': 'jane.doe@gmail.com'}
    returned_user = uc.get_user_by_email(user['email'])
    assert returned_user == user

@pytest.mark.unit
def test_get_user_by_email_with_no_user():
    mockDb = MockDao()
    uc = UserController(dao=mockDb)
    returned_user = uc.get_user_by_email("hejsanhoppsanb@gmail.com")
    assert returned_user is None

@pytest.mark.unit
def test_get_user_by_email_with_more_than_one_entry(capsys):
    mockDb = MockDao()
    uc = UserController(dao=mockDb)
    user =  {
                'firstName': 'John',
                'lastName': 'Doe',
                'email': 'john.doe@gmail.com'}
    returned_user = uc.get_user_by_email(user['email'])
    captured = capsys.readouterr()
    assert captured.out.startswith('Error: more than one user found with mail')
    assert returned_user == user
