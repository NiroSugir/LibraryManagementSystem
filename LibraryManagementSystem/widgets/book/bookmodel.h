#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include "models/book.h"
#include <vector>

using std::vector;

class BookModel
{

public:
    vector<Book> keywordSearch(string searchString);
    Book getBook(string isbn);
    Book getBook(int selectedBookIndex);

private:
    // the books being displayed on the model right now
    vector<Book> visibleBooks{};
    Book *selectedBook{nullptr};
};

#endif // BOOKMODEL_H
