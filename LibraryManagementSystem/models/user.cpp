#include "user.h"

User::User(string _firstName, string _lastName, string _username, string _password, Role _role, bool _validated) :
    firstName{_firstName}, lastName{_lastName}, username{_username}, password{_password}, role{_role}, validated{_validated}
{ }

string User::getFirstName() const
{
    return firstName;
}

string User::getLastName() const
{
    return lastName;
}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

bool User::getValidated() const
{
    return validated;
}

Role User::getRole() const
{
    return role;
}
