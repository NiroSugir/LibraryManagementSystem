#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include "models/book.h"
#include <vector>

using std::vector;

class BookModel
{

public:
    ~BookModel();
    vector<Book> keywordSearch(string searchString);
//    Book getBook(const string &isbn);
    Book getBook(const int &selectedBookIndex);

private:
    // the books being displayed on the model right now
    vector<Book> visibleBooks{};
    Book *selectedBook{nullptr};
};

#endif // BOOKMODEL_H
