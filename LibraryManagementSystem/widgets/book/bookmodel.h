#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include "models/book.h"
#include <vector>

using std::vector;

class BookModel
{

public:
    vector<Book> keywordSearch(string searchString);
//    const Book& getBook(const string &isbn);
    const Book& getBook(const int &selectedBookIndex);

private:
    // the books being displayed on the model right now
    vector<Book> visibleBooks{};
    Book *selectedBook{nullptr};
};

#endif // BOOKMODEL_H
