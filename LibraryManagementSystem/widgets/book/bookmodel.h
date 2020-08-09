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
};

#endif // BOOKMODEL_H
