#include "borrowablebook.h"

BorrowableBook::BorrowableBook(string _isbn, string _name, Author _author, int _year, string _category, string _bookId, string _borrowedBy, int _borrowedOn):
    Book(_isbn, _name, _author, _year, _category), bookId{_bookId}, borrowedBy{_borrowedBy}, borrowedOn{_borrowedOn}
{

}

string BorrowableBook::getBookId() const
{
    return bookId;
}

string BorrowableBook::getBorrowedBy() const
{
    return borrowedBy;
}

int BorrowableBook::getBorrowedOn() const
{
    return borrowedOn;
}
