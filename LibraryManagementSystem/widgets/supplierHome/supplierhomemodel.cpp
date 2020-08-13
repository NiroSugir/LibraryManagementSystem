#include "supplierhomemodel.h"

#include <QDebug>

SupplierHomeModel::SupplierHomeModel(const User *_currentUser)
{
    currentUser = _currentUser;
}

void SupplierHomeModel::sellBook(SellableBook book)
{
    DbConnection connection;

    // search the db
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query{QSqlDatabase::database("sell-book")};

        query.exec("begin transaction;");

        // search for book using isbn (assume book info is correct for books in the system)
        bool bookExists{false};

        const bool prepareBookExists = query.prepare("select isbn from books where isbn = :isbn");
        if (prepareBookExists) {
            query.bindValue(":isbn", book.getIsbn().c_str());
            query.exec();

            bookExists = query.next();
        } else {
            return rollback(db, query);
        }

        // add book to the list of books
        if (!bookExists) {
            query.clear();
            const bool prepareAddBook = query.prepare("insert into books (isbn, title, genre, year, author_id) values (:isbn, :title, :gentre, :year, :author_id)");
            if (prepareAddBook) {
                query.bindValue(":isbn", book.getIsbn().c_str());
                query.bindValue(":title", book.getName().c_str());
                query.bindValue(":genre", book.getCategory().c_str());
                query.bindValue(":year", book.getYear());
                query.bindValue(":author_id", book.getAuthor().getId().c_str());
            } else {
                return rollback(db, query);
            }

            query.exec();
            if (query.lastError().isValid()) {
                return rollback(db, query);
            }

            query.clear();
        }

        // add this book for sale by this user for the set price
        const bool prepareList4Sale = query.prepare("insert into books_for_sale (isbn, price, seller_id) values (:isbn, :price, :seller_id)");
        if (prepareList4Sale) {
            query.bindValue(":isbn", book.getIsbn().c_str());
            query.bindValue(":price", book.getPrice());
            query.bindValue(":seller_id", book.getSellerId().c_str());

            query.exec();
            if (query.lastError().isValid()) {
                return rollback(db, query);
            }
        }

        query.exec("commit");
    } else {
        // TODO: throw call support error
    }

}

void SupplierHomeModel::rollback(QSqlDatabase &db, QSqlQuery &query)
{
    // TODO: throw error
    query.exec("rollback");
    qDebug() << query.lastError().text();
    query.clear();
    db.close();
}
