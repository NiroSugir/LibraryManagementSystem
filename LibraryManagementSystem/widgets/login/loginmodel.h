#ifndef LOGINMODEL_H
#define LOGINMODEL_H

#include <iostream>
#include "models/user.h"
#include "dbconnection.h"

using std::string;

class LoginModel
{

public:
    User login(const string &username, const string &password);
};

#endif // LOGINMODEL_H
