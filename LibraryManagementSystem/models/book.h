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
    int copies;

public:
    Book(string _name, string _author, int _year, string _isbn, string _publisher, string _category, int copies);

    string getName() const;
    string getAuthor() const;
    int getYear() const;
    string getIsbn() const;
    string getPublisher() const;
    string getCategory() const;
    int getCopies() const;
};

#endif // BOOK_H
