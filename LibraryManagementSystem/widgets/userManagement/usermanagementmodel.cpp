#include "usermanagementmodel.h"

#include <QDebug>
#include "widgets/_helper/erroralert.h"

UserManagementModel::~UserManagementModel()
{
    if (selectedUser) {
        delete selectedUser;
        selectedUser = NULL;
    }
}

vector<User> UserManagementModel::loadUsers(ValidationStatus _validationStatus)
{
    DbConnection connection;
    validationStatus = _validationStatus;

    QSqlDatabase db = connection.getDb();

    users.clear();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query{QSqlDatabase::database("load-users")};

        string q = "select user_id, username, first_name, last_name, role as r, validated as v from Users";

        if (_validationStatus == ValidationStatus::Validated) {
            q += " where validated = 1";
        } else if (_validationStatus == ValidationStatus::Unvalidated) {
            q += " where validated = 0";
        }

        query.exec(q.c_str());

        if (query.lastError().isValid()) {
            ErrorAlert{};
            qDebug() << query.lastError();
            db.close();
            return users;
        } else {
            while (query.next()) {
                users.push_back(User{
                    //user id
                    query.value(0).toString().toStdString(),
                    // username
                    query.value(1).toString().toStdString(),
                    // first name
                    query.value(2).toString().toStdString(),
                    // lastname
                    query.value(3).toString().toStdString(),
                    // password
                    "",
                    // role
                    (Role) query.value(4).toInt(),
                    // validate
                    query.value(5).toBool()
                });
            }

            db.close();
            return users;
        }

    }
}

User UserManagementModel::changeSelectedUser(int selectedIndex)
{
    selectedUser = new User{users[selectedIndex]};

    return *selectedUser;
}

User UserManagementModel::approveSelectedUser()
{
    DbConnection connection;
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query{QSqlDatabase::database("approve-user")};

        if (query.exec(("update Users set validated = 1 where user_id = " + selectedUser->getId()).c_str())) {
            // success
            selectedUser->setValidated(true);
            db.close();
            return *selectedUser;
        } else {
            // failed
            ErrorAlert{};
            qDebug() << query.lastError().text();
            db.close();
        }
    } else {
        ErrorAlert{};
    }
}
