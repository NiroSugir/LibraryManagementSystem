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

vector<BorrowableBook> BookModel::keywordSearch(string searchString)
{
    DbConnection connection;
    selectedBook = nullptr;
    visibleBooks.clear();

    // search the db
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
       QSqlQuery query{QSqlDatabase::database("keyword-search")};

       /*
        select
        Books.isbn, books.title, books.genre, Books.year,
        LibraryBooks.library_book_id, LibraryBooks.borrowed_by, LibraryBooks.borrowed_on,
        Authors.author_id, Authors.first_name, Authors.last_name

        from LibraryBooks

        left join Books_For_Sale
            on Books_For_Sale.sale_id = LibraryBooks.purchase_id
        left join Books
            on Books_For_Sale.isbn = Books.isbn
        left join Authors
            on Books.author_id = Authors.author_id

        where (
            books.title like "%farm%" OR
            books.isbn like "" OR
            books.genre like "" OR
            Authors.first_name like "" OR
            Authors.last_name like ""
        )

        */

       // use prepared statements to prevent sql injection attacks
       string q = "select "
               "Books.isbn, books.title, books.genre, Books.year, "
               "LibraryBooks.library_book_id, LibraryBooks.borrowed_by, LibraryBooks.borrowed_on, "
               "Authors.author_id, Authors.first_name, Authors.last_name "

               "from LibraryBooks "

               "left join Books_For_Sale "
                   "on Books_For_Sale.sale_id = LibraryBooks.purchase_id "
               "left join Books "
                   "on Books_For_Sale.isbn = Books.isbn "
               "left join Authors "
                   "on Books.author_id = Authors.author_id "

               "where ("
                   "books.title like :keyword OR "
                   "books.isbn like :keyword OR "
                   "books.genre like :keyword OR "
                   "Authors.first_name like :keyword OR "
                   "Authors.last_name like :keyword "
               ")";


       const bool successfullyPrepared = query.prepare(q.c_str());

       if (successfullyPrepared) {
            qDebug() << "successfully prepared statement";
            query.bindValue(":keyword", ("%" + searchString + "%").c_str());

            query.exec();

            if (query.lastError().isValid()) {
                qDebug() << query.lastError();
                return visibleBooks;
            } else {
                while(query.next()) {
                    Author author{
                        query.value(7).toString().toStdString(),
                                query.value(8).toString().toStdString(),
                                query.value(9).toString().toStdString(),
                    };
                    visibleBooks.push_back(BorrowableBook{
                       // isbn
                       query.value(0).toString().toStdString(),
                       // title
                       query.value(1).toString().toStdString(),
                       // author
                       author,
                       // year
                       query.value(3).toInt(),
                       // category
                       query.value(2).toString().toStdString(),
                       // book id
                       query.value(4).toString().toStdString(),
                       // borrowed by
                       query.value(5).toString().toStdString(),
                       // borrowed on
                       query.value(6).toInt()
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

BorrowableBook BookModel::getBook(const int &selectedBookIndex)
{
    selectedBook = &visibleBooks[selectedBookIndex];
    return *selectedBook;
}

BorrowableBook BookModel::borrowBook()
{
    DbConnection connection;

    // search the db
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
       QSqlQuery query{QSqlDatabase::database("borrow-book")};

       query.prepare("update LibraryBooks set borrowed_by = :borrower_id where library_book_id = :book_id");
       if (query.lastError().isValid()) {
           qDebug() << query.lastError().text();
       }

       qDebug() << "selectedBook->getBookId().c_str(): " << selectedBook->getBookId().c_str();
       query.bindValue(":book_id", selectedBook->getBookId().c_str());
       qDebug() << "currentUser->getId().c_str()" << currentUser->getId().c_str();
       query.bindValue(":borrower_id", currentUser->getId().c_str());
       query.exec();


       if (query.lastError().isValid()) {
           qDebug() << query.lastError().text();
       }
        db.close();

       int selectedBookIndex{0};
       for (const BorrowableBook &book: visibleBooks) {
           if (book.getBookId() == selectedBook->getBookId()) {
               break;
           }

           selectedBookIndex++;
       }

       return getBook(selectedBookIndex);
    } else {
        // todo:
    }

}
