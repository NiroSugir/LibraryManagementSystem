#ifndef USER_H
#define USER_H

#include <iostream>
#include "models/role.h"
#include "dbconnection.h"

using std::string;

class User
{
private:
    string id{nullptr};
    string firstName{nullptr};
    string lastName{nullptr};
    string username{nullptr};
    string password{nullptr};

    Role role{Role::Member};
    bool validated{false};

public:
    static int passwordHash(const string &_password);

    static void usernameIsValid(const string &_username);
    static void passwordIsValid(const string &_password);

    User(
        string _firstName,
        string _lastName,
        string _username,
        string _password,
        Role _role,
        bool _validated
    );

    User(
        string _id,
        string _username,
        string _firstName,
        string _lastName,
        string _password,
        Role _role,
        bool _validated
    );

    string getFirstName() const;
    string getLastName() const;
    string getUsername() const;
    string getPassword() const;
    Role getRole() const;
    bool getValidated() const;

    void save();
};

#endif // USER_H
