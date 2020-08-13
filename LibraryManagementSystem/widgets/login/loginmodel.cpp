#include "loginmodel.h"

#include <QDebug>

User LoginModel::login(const string &username, const string &password)
{
    DbConnection connection;
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query;

        // use prepared statements to prevent sql injection attacks
        const bool successfullyPrepared = query.prepare("SELECT username, first_name, last_name, password, role, validated, user_id FROM Users WHERE (username = :username AND password = :password) LIMIT 1");

        if (successfullyPrepared) {
            query.bindValue(":username", username.c_str());
            query.bindValue(":password", User::passwordHash(password));

            if (query.exec()) {
                if (query.next()) {
                    // user found
                    User user{
                        //userid
                        query.value(6).toString().toStdString(),
                        // usrname
                        query.value(0).toString().toStdString(),
                        // first name
                        query.value(1).toString().toStdString(),
                        // last name
                        query.value(2).toString().toStdString(),
                        // password
                        // TODO: remove password retrieval. not necessary for app
                        "",
                        // role
                        (Role) query.value(4).toUInt(),
                        // validated
                        query.value(5).toBool()
                    };

                    db.close();
                    return user;
                } else {
                    query.clear();
                    db.close();

                    // user not found
                    throw "Credentials not found! Please retype your username & password or signup!";
                }
            } else {
                db.close();

                // TODO: log: "failed to query database using username[] & password []"
                throw "Please try again later";
            }

        } else {
            db.close();

            // TODO: log: "failed to prepare statement"
            throw "Intenal DB Error! Please change what you entered and try again.";
        }

        db.close();
    } else {
        // TODO: log: "failed to open db"
        throw "Internal DB Error! Could not access database. Please wait a while and try again. If problem persists, reinstall the app or call at 1-800-SHOULD-HAVE-PAID-FOR-SUPPORT ext. HAHA";
    }
}
