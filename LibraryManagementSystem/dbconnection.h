#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QObject>
#include <QSql>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class DbConnection
{
private:
    QSqlDatabase db;

public:
    DbConnection();

    QSqlDatabase getDb() const;
};

#endif // DBCONNECTION_H
