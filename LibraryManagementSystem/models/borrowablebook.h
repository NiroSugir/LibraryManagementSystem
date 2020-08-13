#ifndef BORROWABLEBOOK_H
#define BORROWABLEBOOK_H

#include "book.h"

using std::string;

class BorrowableBook: public Book
{
    string bookId;
    string borrowedBy;
    int borrowedOn;

public:
    BorrowableBook(string _isbn, string _name, Author _author, int _year, string _category, string _bookId, string _borrowedBy, int _borrowedOn);

    string getBookId() const;
    string getBorrowedBy() const;
    int getBorrowedOn() const;
};

#endif // BORROWABLEBOOK_H
