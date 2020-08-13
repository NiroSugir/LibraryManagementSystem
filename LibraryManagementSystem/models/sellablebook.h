#ifndef SELLABLEBOOK_H
#define SELLABLEBOOK_H

#include "models/book.h"
#include "models/user.h"

class SellableBook: public Book
{
protected:
    string saleId;
    User seller;
    double price;

public:
    SellableBook(string _saleId, string _isbn, string _name, Author _author, int _year, string _category, User _seller, double _price);

    string getSaleId() const;
    double getPrice() const;
    string getSellerId() const;
};

#endif // SELLABLEBOOK_H
