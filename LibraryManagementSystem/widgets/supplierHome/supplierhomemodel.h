#ifndef SUPPLIERHOMEMODEL_H
#define SUPPLIERHOMEMODEL_H

#include "models/user.h"
#include <vector>
#include "dbconnection.h"
#include "models/sellablebook.h"

using std::vector;

class SupplierHomeModel
{
public:
    SupplierHomeModel(const User *_currentUser);
    void sellBook(SellableBook _book);

private:
    // logged in user (if any)
    const User *currentUser{nullptr};

    // the books being displayed on the model right now
    vector<Book> visibleBooks{};

    //currently selected book (pointer to a book on the list of visible books)
    Book *selectedBook{nullptr};

    void rollback(QSqlDatabase &db, QSqlQuery &query);
};

#endif // SUPPLIERHOMEMODEL_H
