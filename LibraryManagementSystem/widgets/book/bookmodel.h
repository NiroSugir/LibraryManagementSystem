#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include "models/book.h"
#include <vector>
#include "dbconnection.h"

using std::vector;

class BookModel
{

public:
    ~BookModel();
    vector<Book> keywordSearch(string searchString);
    Book getBook(const int &selectedBookIndex);

private:
    // the books being displayed on the model right now
    vector<Book> visibleBooks{};

    //currently selected book (pointer to a book on the list of visible books)
    Book *selectedBook{nullptr};

    DbConnection connection;
};

#endif // BOOKMODEL_H
