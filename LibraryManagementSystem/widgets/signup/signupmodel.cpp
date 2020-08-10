#include "signupmodel.h"

void SignupModel::signup(
    const string &firstName,
    const string &lastName,
    const string &username,
    const string &password,
    const string &verifyPassword,
    const Role &role
) {
    // TODO: validate if alphabetic
    if (firstName.size() < 2)
        throw "First Name's too short";

    // TODO: validate if alphabetic
    if (lastName.size() < 2)
        throw "Last Name's too short";

    User::usernameIsValid(username);

    User::passwordIsValid(password);

    if (password != verifyPassword)
        throw "Passwords do not match";

    User user{ firstName, lastName, username, password, role, false };

    try {
        user.save();
    } catch (const char* msg) {
        throw msg;
    }
}
