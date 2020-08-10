#ifndef SIGNUPMODEL_H
#define SIGNUPMODEL_H

#include <iostream>
#include "models/user.h"

using std::string;

class SignupModel
{
public:
    void signup(
        const string &firstName,
        const string &lastName,
        const string &username,
        const string &password,
        const string &verifyPassword,
        const Role &role
     );
};

#endif // SIGNUPMODEL_H
