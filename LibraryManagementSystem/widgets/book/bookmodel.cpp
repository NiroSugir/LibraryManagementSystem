#include "bookmodel.h"

#include <QDebug>

BookModel::BookModel(const User *_currentUser)
{
    currentUser = _currentUser;
}

vector<string> BookModel::getCategories()
{
    DbConnection connection;

    // search the db
    QSqlDatabase db = connection.getDb();

    vector<string> categories{};

    db.open();
    if (db.isOpen()) {
        QSqlQuery query{QSqlDatabase::database("keyword-search")};

        if (query.exec("select name from Categories;")) {
            while (query.next()) {
                categories.push_back(query.value(0).toString().toStdString());
            }

            db.close();

            return categories;
        } else {
            db.close();
            // TODO: throw error
            qDebug() << query.lastError();
        }

    } else {
        db.close();
        // TODO: throw contact support error
    }
}

vector<Book> BookModel::keywordSearch(string searchString)
{
    DbConnection connection;
    selectedBook = nullptr;
    visibleBooks.clear();

    // search the db
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
       QSqlQuery query{QSqlDatabase::database("keyword-search")};

       // use prepared statements to prevent sql injection attacks
       const bool successfullyPrepared = query.prepare("select isbn, title, author, publisher, genre, copies, year from books where ( title LIKE :keyword OR author LIKE :keyword OR isbn LIKE :keyword )");

       if (successfullyPrepared) {
            qDebug() << "successfully prepared statement";
            query.bindValue(":keyword", ("%" + searchString + "%").c_str());

            query.exec();

            if (query.lastError().isValid()) {
                qDebug() << query.lastError();
                return visibleBooks;
            } else {
                while(query.next()) {
                    visibleBooks.push_back(Book{
                                               // isbn
                                               query.value(0).toString().toStdString(),
                                               // title
                                               query.value(1).toString().toStdString(),
                                               // author
                                               // TODO: replace with real author
//                                               query.value(2).toString().toStdString(),
                                               Author{"fake id", "fake first name", "fake last name"},
                                               // year
                                                query.value(6).toInt(),
                                                // genre
                                                query.value(4).toString().toStdString(),

                    });
                }
            }
       } else {
           qDebug() << "fail preparing statement";
           qDebug() << query.lastError();
       }
    }

    return visibleBooks;
}

Book BookModel::getBook(const int &selectedBookIndex)
{
    selectedBook = &visibleBooks[selectedBookIndex];
    return *selectedBook;
}
