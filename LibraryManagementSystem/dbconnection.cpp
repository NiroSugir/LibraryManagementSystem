#include "dbconnection.h"

QSqlDatabase DbConnection::getDb() const
{
    return db;
}

DbConnection::DbConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("super_secret_database_please_dont_open.sqlite3");
}
