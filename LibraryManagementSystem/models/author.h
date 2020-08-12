#ifndef AUTHOR_H
#define AUTHOR_H

#include <iostream>

using std::string;

class Author
{
private:
    string id{""};
    string firstName{""};
    string lastName{""};

public:
    Author(string _id = "", string _firstName = "", string _lastName = "");
    string getId() const;
    string getFirstName() const;
    void setFirstName(const string &value);
    string getLastName() const;
    void setLastName(const string &value);
};

#endif // AUTHOR_H
