#ifndef BOOK_H
#define BOOK_H

#include <iostream>

using std::string;

class Book
{
private:
    string name;
    string author;
    int year;
    string isbn;
    string publisher;
    string category;

public:
    static Book loadFromDb(string isbn);

    Book(string _name, string _author, int _year, string _isbn, string _publisher, string _category);
};

#endif // BOOK_H