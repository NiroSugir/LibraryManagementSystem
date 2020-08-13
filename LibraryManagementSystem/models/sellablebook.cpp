#include "sellablebook.h"

double SellableBook::getPrice() const
{
    return price;
}

string SellableBook::getSellerId() const
{
    return seller.getId();
}

SellableBook::SellableBook(string _isbn, string _name, Author _author, int _year, string _category, User _seller, double _price):
    Book::Book{_isbn, _name, _author, _year, _category}, seller{_seller}, price{_price}
{
    if (price <= 0.0) {
        throw "Price should be a positive number";
    }
}
