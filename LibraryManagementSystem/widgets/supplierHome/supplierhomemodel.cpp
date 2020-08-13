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
            const bool prepareAddBook = query.prepare("insert into books (isbn, title, genre, year, author_id) values (:isbn, :title, :genre, :year, :author_id)");
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

            // link book to author in conjunction table
            const bool prepareLinkBookAuthor = query.prepare("insert into books_authors (book_isbn, author_id) values (:isbn, :author_id)");
            if (prepareLinkBookAuthor) {
                query.bindValue(":isbn", book.getIsbn().c_str());
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

vector<SellableBook> SupplierHomeModel::getBooksListedForSaleByThisUser()
{
    DbConnection connection;

    // search the db
    QSqlDatabase db = connection.getDb();

    booksForSale.clear();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query{QSqlDatabase::database("get-listed-books")};

        /*
            select Books.isbn, books.title, books.genre, Books.year, Books_For_Sale.price, Authors.first_name, Authors.last_name
            from Books_For_Sale
            left join Books
            on Books_For_Sale.isbn = books.isbn
            left join Authors
            on Books.author_id = Authors.author_id
            where Books_For_Sale.seller_id = 3 and Books_For_Sale.purchaser_id = 0;
         */

        query.exec(((string) "select Books.isbn, books.title, books.genre, Books.year, Books_For_Sale.price, Authors.author_id, Authors.first_name, Authors.last_name, Books_For_Sale.sale_id "
                   "from Books_For_Sale left join Books on Books_For_Sale.isbn = books.isbn left join "
                   "Authors on Books.author_id = Authors.author_id where Books_For_Sale.purchaser_id = 0 and Books_For_Sale.seller_id = " + currentUser->getId()).c_str());

        while(query.next()) {
            Author author {
                query.value(5).toString().toStdString(),
                query.value(6).toString().toStdString(),
                query.value(7).toString().toStdString(),
            };

            booksForSale.push_back(SellableBook{
                // sale id
                 query.value(8).toString().toStdString()                       ,
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
                // seller
                *currentUser,
                // price
                query.value(4).toDouble(),
            });
        }
    } else {
        // TODO: throw contact support error
    }

    return booksForSale;
}

void SupplierHomeModel::rollback(QSqlDatabase &db, QSqlQuery &query)
{
    qDebug() << query.lastError().text();
    // TODO: throw error
    query.exec("rollback");
    query.clear();
    db.close();
}
