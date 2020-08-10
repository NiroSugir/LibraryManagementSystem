#include "dbconnection.h"

QSqlDatabase DbConnection::getDb() const
{
    return db;
}

DbConnection::DbConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("super_secret_database_dont_open.sqlite3");
}
