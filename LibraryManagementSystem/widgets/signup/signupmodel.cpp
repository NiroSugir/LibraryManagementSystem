#include "signupmodel.h"

#include <QDebug>

void SignupModel::signup(
    const string &firstName,
    const string &lastName,
    const string &username,
    const string &password,
    const string &verifyPassword,
    const Role &role
) {
    // TODO: validate if alphabetic
    qDebug() << "role: " << role;

    if (firstName.size() < 2)
        throw "First Name's too short";

    if (lastName.size() < 2)
        throw "Last Name's too short";

    if (username.size() < 4)
        throw "Username must be at least 4 characters long.";

    if (username.size() > 20)
        throw "Username is too long (max 20 characters).";

    if (password.length() < 8)
        throw "Password is too short. It must be at least 8 characters long";

    if (password != verifyPassword)
        throw "Passwords do not match";

    const User user{ firstName, lastName, username, password, role, false };


    // TODO: save to database
    try {

    } catch (const char* msg) {
        throw "There's a problem with your Database!";
    }
}
