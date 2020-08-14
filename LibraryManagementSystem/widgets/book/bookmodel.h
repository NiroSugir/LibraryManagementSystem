#ifndef BOOKMODEL_H
#define BOOKMODEL_H

//#include "models/book.h"
#include "models/user.h"
#include <vector>
#include "dbconnection.h"
#include "models/borrowablebook.h"

using std::vector;

class BookModel
{

public:
    BookModel(const User *_currentUser);
    vector<string> getCategories();
    vector<BorrowableBook> keywordSearch(string searchString);
    BorrowableBook getBook(const int &selectedBookIndex);
    BorrowableBook borrowBook();


private:
    // logged in user (if any)
    const User *currentUser{nullptr};

    // the books being displayed on the model right now
    vector<BorrowableBook> visibleBooks{};

    //currently selected book (pointer to a book on the list of visible books)
    BorrowableBook *selectedBook{nullptr};
};

#endif // BOOKMODEL_H
