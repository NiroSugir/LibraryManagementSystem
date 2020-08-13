#ifndef USER_H
#define USER_H

#include <iostream>
#include "models/role.h"
#include "dbconnection.h"

using std::string;

class User
{
private:
    string id{""};
    string firstName{""};
    string lastName{""};
    string username{""};
    string password{""};

    Role role{Role::Guest};
    bool validated{false};

public:
    static int passwordHash(const string &_password);

    static void usernameIsValid(const string &_username);
    static void passwordIsValid(const string &_password);

    // DEPRECATED
    // USE THE OTHER CONSTRUCTOR WITH THE ID
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
    bool isValidated() const;

    void save();
    string getId() const;
    void setValidated(bool value);
};

#endif // USER_H
