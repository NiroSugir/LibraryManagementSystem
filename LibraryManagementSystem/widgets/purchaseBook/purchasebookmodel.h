#ifndef PURCHASEBOOKMODEL_H
#define PURCHASEBOOKMODEL_H

#include "models/user.h"
#include <vector>
#include "dbconnection.h"
#include "models/sellablebook.h"

using std::vector;

class PurchaseBookModel
{
public:
    PurchaseBookModel(const User *_currentUser);
    void purchaseBook(SellableBook _book);
    vector<SellableBook> getBooksListedForSale();
    SellableBook selectBook(int selectedIndex);

private:
    // logged in user (if any)
    const User *currentUser{nullptr};

    // the books being displayed on the view right now
    vector<SellableBook> booksForSale{};

    //currently selected book (pointer to a book on the list of visible books)
    SellableBook *selectedBook{nullptr};
};

#endif // PURCHASEBOOKMODEL_H
