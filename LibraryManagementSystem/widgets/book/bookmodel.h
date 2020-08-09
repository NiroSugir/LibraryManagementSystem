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

private:
    // the books being displayed on the model right now
    vector<Book> visibleBooks{};
};

#endif // BOOKMODEL_H
