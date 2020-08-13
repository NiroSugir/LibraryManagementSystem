#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include "models/author.h"

using std::string;

class Book
{
protected:
    string isbn;
    string name;
    Author author;
    int year;
    string category;

public:
    Book(string _isbn, string _name, Author _author, int _year, string _category);

    virtual string getIsbn() const;
    virtual string getName() const;
    virtual int getYear() const;
    virtual string getCategory() const;
    virtual Author getAuthor() const;

    // TODO: remove this and use getAuthor().getnames...
    virtual string getAuthorName() const;
};

#endif // BOOK_H
