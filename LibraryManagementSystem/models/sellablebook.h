#ifndef SELLABLEBOOK_H
#define SELLABLEBOOK_H

#include "models/book.h"
#include "models/user.h"

class SellableBook: public Book
{
protected:
    User seller;
    double price;

public:
    SellableBook(string _isbn, string _name, string _author, int _year, string _category, User _seller, double _price);

    double getPrice() const;
    string getSellerId() const;

};

#endif // SELLABLEBOOK_H
