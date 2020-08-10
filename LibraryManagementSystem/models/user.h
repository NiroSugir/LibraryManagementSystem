#ifndef USER_H
#define USER_H

#include <iostream>
#include "models/role.h"
#include "dbconnection.h"

using std::string;

class User
{
private:
    string firstName{nullptr};
    string lastName{nullptr};
    string username{nullptr};
    string password{nullptr};

    Role role{Role::Member};
    bool validated{false};

    DbConnection connection;

public:
    static int passwordHash(const string &_password);
    static bool isValidUsername(const string &_username);
    static bool isValidPassword(const string &_password);

    User(
        string _firstName,
        string _lastName,
        string _username,
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
