#include "user.h"

#include <QDebug>

// terrible hashing alogorithm from:
// https://codereview.stackexchange.com/questions/178911/c-hashing-passwords-simple-algorithm-using-rand
int User::passwordHash(const string &_password)
{
    unsigned int hash = 0;

    const unsigned int size = _password.length();
    for (signed char letter : _password) {
       srand(size * letter);
       hash += 33 + rand() % 92;
    }

    return hash;
}

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

void User::save()
{
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query;

        // use prepared statements to prevent sql injection attacks
        const bool successfullyPrepared = query.prepare("INSERT INTO Users (username,first_name,last_name,password,role,validated) VALUES (:username,:first_name,:last_name,:password,:role,:validated)");

        if (successfullyPrepared) {
            query.bindValue(":username", username.c_str());
            query.bindValue(":first_name", firstName.c_str());
            query.bindValue(":last_name", lastName.c_str());
            // TODO: sha() hash password before storing.
            query.bindValue(":password", passwordHash(password));
            query.bindValue(":role", role);
            query.bindValue(":validated", validated ? 1 : 0);
            query.exec();

            if (query.lastError().isValid()) {
                if (query.lastError().text().contains("UNIQUE constraint failed")) {
                    throw "That username is already taken. Please try another.";
                } else {
                    throw "Sign up failed! Please contact support.";
                }

                qDebug() << query.lastError();
            }
        } else {
            // TODO: log: "failed to prepare statement"
            throw "Intenal DB Error! Please change what you entered and try again.";
        }

        query.clear();
        db.close();
    } else {
        // TODO: log: "failed to open db"
        throw "Internal DB Error! Couldnot access database. Please wait a while and try again. If problem persists, reinstall the app or call at 1-800-SHOULD-HAVE-PAID-FOR-SUPPORT ext. HAHA";
    }
}

Role User::getRole() const
{
    return role;
}
