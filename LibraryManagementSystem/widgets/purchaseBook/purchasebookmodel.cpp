#include "purchasebookmodel.h"

#include <QDebug>
#include "widgets/_helper/erroralert.h"

PurchaseBookModel::PurchaseBookModel(const User *_currentUser): currentUser{_currentUser}
{ }

void PurchaseBookModel::purchaseBook(SellableBook _book)
{
    DbConnection connection;

    // search the db
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query{QSqlDatabase::database("purchase-book")};

        // start transaction
        query.exec("begin transaction;");

        if (query.lastError().isValid()) {
            qDebug() << query.lastError().text();
            ErrorAlert{};
        }

        // set the purchased by id to this staff user
        query.prepare("update books_for_sale set purchaser_id = :staff_id where sale_id = :sale_id");
        query.bindValue(":staff_id", currentUser->getId().c_str());
        query.bindValue(":sale_id", _book.getSaleId().c_str());
        query.exec();

        if (query.lastError().isValid()) {
            qDebug() << query.lastError().text();
            ErrorAlert{};
        }

        query.clear();

        // add entry to library books table
        query.prepare("insert into librarybooks (purchase_id) values (:sale_id)");
        query.bindValue(":sale_id", _book.getSaleId().c_str());
        query.exec();

        if (query.lastError().isValid()) {
            qDebug() << query.lastError().text();
            ErrorAlert{};
        }

        // end transaction
        query.exec("commit");

        if (query.lastError().isValid()) {
            qDebug() << query.lastError().text();
            // todo: throw contact support error
        }

        db.close();
    } else {
        ErrorAlert{};
    }
}

vector<SellableBook> PurchaseBookModel::getBooksListedForSale()
{
    DbConnection connection;

    // search the db
    QSqlDatabase db = connection.getDb();

    booksForSale.clear();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query{QSqlDatabase::database("get-listed-books")};

        const char *queryString{"select Books.isbn, books.title, books.genre, Books.year, "
                           "Books_For_Sale.price, "
                           "Authors.author_id, Authors.first_name, Authors.last_name, "
                           "Users.user_id, Users.username, Users.first_name, Users.last_name, Users.role, Users.validated, "
                           "Books_For_Sale.sale_id "
                           "from Books_For_Sale "
                           "left join Books "
                               "on Books_For_Sale.isbn = books.isbn "
                           "left join Authors "
                               "on Books.author_id = Authors.author_id "
                           "left join Users "
                           "on Users.user_id = Books_For_Sale.seller_id "
                           "where Books_For_Sale.purchaser_id = 0"};

        query.exec(queryString);
        if (query.lastError().isValid()) {
            qDebug() << query.lastError().text();
            ErrorAlert{};
        }

        while(query.next()) {
            Author author {
                query.value(5).toString().toStdString(),
                query.value(6).toString().toStdString(),
                query.value(7).toString().toStdString(),
            };

            User seller {
                // user id
                query.value(8).toString().toStdString(),
                // username
                query.value(9).toString().toStdString(),
                // first name
                query.value(10).toString().toStdString(),
                // last name
                query.value(11).toString().toStdString(),
                // password
                "",
                // role
                (Role) query.value(12).toUInt(),
                // validated
                query.value(13).toUInt() == 1 ? true : false,
            };

            booksForSale.push_back(SellableBook{
                // sale id
                query.value(14).toString().toStdString(),
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
                seller,
                // price
                query.value(4).toDouble(),
            });
        }
    } else {
        ErrorAlert{};
    }

    return booksForSale;
}

SellableBook PurchaseBookModel::selectBook(int selectedIndex)
{
    selectedBook = &booksForSale[selectedIndex];
    return *selectedBook;
}
