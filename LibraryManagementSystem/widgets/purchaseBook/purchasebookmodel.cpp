#include "purchasebookmodel.h"

#include <QDebug>

PurchaseBookModel::PurchaseBookModel(const User *_currentUser)
{

}

void PurchaseBookModel::purchaseBook(SellableBook _book)
{

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
                           "Users.user_id, Users.username, Users.first_name, Users.last_name, Users.role, Users.validated "
                           "from Books_For_Sale "
                           "left join Books "
                               "on Books_For_Sale.isbn = books.isbn "
                           "left join Authors "
                               "on Books.author_id = Authors.author_id "
                           "left join Users "
                           "on Users.user_id = Books_For_Sale.seller_id "
                           "where Books_For_Sale.purchaser_id = 0"};

        query.exec(queryString);

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
        // TODO: throw contact support error
    }

    return booksForSale;
}
