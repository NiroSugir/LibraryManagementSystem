#include "author.h"

string Author::getId() const
{
    return id;
}

string Author::getFirstName() const
{
    return firstName;
}

void Author::setFirstName(const string &value)
{
    firstName = value;
}

string Author::getLastName() const
{
    return lastName;
}

void Author::setLastName(const string &value)
{
    lastName = value;
}

Author::Author(string _id, string _firstName, string _lastName):id{_id}, firstName{_firstName}, lastName{_lastName}
{
    
}
