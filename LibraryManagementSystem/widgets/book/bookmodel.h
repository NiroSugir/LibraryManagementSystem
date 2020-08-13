#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include "models/book.h"
#include "models/user.h"
#include <vector>
#include "dbconnection.h"

using std::vector;

class BookModel
{

public:
    BookModel(const User *_currentUser);
    vector<string> getCategories();
    vector<Book> keywordSearch(string searchString);
    Book getBook(const int &selectedBookIndex);

private:
    // logged in user (if any)
    const User *currentUser{nullptr};

    // the books being displayed on the model right now
    vector<Book> visibleBooks{};

    //currently selected book (pointer to a book on the list of visible books)
    Book *selectedBook{nullptr};


};

#endif // BOOKMODEL_H
