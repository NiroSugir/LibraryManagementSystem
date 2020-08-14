#include "user.h"

#include <QDebug>

// simple/weak hashing alogorithm from:
// https://codereview.stackexchange.com/questions/178911/c-hashing-passwords-simple-algorithm-using-rand
string User::getId() const
{
    return id;
}

void User::setValidated(bool value)
{
    validated = value;
}

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

void User::usernameIsValid(const string &_username)
{
    if (_username.size() < 4) throw "Username must be at least 4 characters long.";
    if (_username.size() > 20) throw "Username is too long (max 20 characters).";

    // TODO: alphanumeric
    // TODO: starts with letters
}

void User::passwordIsValid(const string &_password)
{
    if (_password.size() < 8) throw "Password is too short. It must be at least 8 characters long";
}

User::User(string _firstName, string _lastName, string _username, string _password, Role _role, bool _validated) :
    firstName{_firstName}, lastName{_lastName}, username{_username}, password{_password}, role{_role}, validated{_validated}
{
}

User::User(string _id, string _username, string _firstName, string _lastName, string _password, Role _role, bool _validated):
    id{_id}, username{_username}, firstName{_firstName}, lastName{_lastName}, password{_password}, role{_role}, validated{_validated}
{
}

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

bool User::isValidated() const
{
    return validated;
}

void User::save()
{
    DbConnection connection;
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query{QSqlDatabase::database("load-user")};

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
                    query.clear();
                    db.close();

                    throw "That username is already taken. Please try another.";
                } else {
                    query.clear();
                    db.close();

                    throw "Sign up failed! Please contact support.";
                }

                qDebug() << query.lastError();
            }
        } else {
            query.clear();
            db.close();

            throw "Intenal DB Error! Please change what you entered and try again.";
        }

        query.clear();
        db.close();
    } else {
        throw "Internal DB Error! Could not access database. Please wait a while and try again. If problem persists, reinstall the app or call at 1-800-SHOULD-HAVE-PAID-FOR-SUPPORT ext. HAHA";
    }
}

Role User::getRole() const
{
    return role;
}
