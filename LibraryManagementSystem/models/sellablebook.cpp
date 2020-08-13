#include "sellablebook.h"

double SellableBook::getPrice() const
{
    return price;
}

string SellableBook::getSellerId() const
{
    return seller.getId();
}

string SellableBook::getSaleId() const
{
    return saleId;
}

SellableBook::SellableBook(string _saleId, string _isbn, string _name, Author _author, int _year, string _category, User _seller, double _price):
    Book::Book{_isbn, _name, _author, _year, _category}, saleId{_saleId}, seller{_seller}, price{_price}
{
    if (price <= 0.0) {
        throw "Price should be a positive number";
    }
}
