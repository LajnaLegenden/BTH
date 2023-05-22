# mocks a dao for users like usercontroller does

class MockDao:
    def __init__(self):
        self.users = [
            {
                'firstName': 'Jane',
                'lastName': 'Doe',
                'email': 'jane.doe@gmail.com'},
            {
                'firstName': 'John',
                'lastName': 'Doe',
                'email': 'john.doe@gmail.com'},
            {'firstName': 'John',
                'lastName': 'Smith',
                'email': 'john.doe@gmail.com'}
        ]

    def find(self, query):
        if query['email']:
            users = []
            for user in self.users:
                if user['email'] == query['email']:
                    users.append(user)
            return users
        return self.users

    def insert(self, data):
        self.users.append(data)

    def update(self, query, data):
        for user in self.users:
            if user['email'] == query['email']:
                user.update(data)
                return True
        return False

    def delete(self, query):
        for user in self.users:
            if user['email'] == query['email']:
                self.users.remove(user)
                return True
        return False
