#include "book.h"

int Book::getCopies() const
{
    return copies;
}

string Book::getName() const
{
    return name;
}

string Book::getAuthor() const
{
    return author;
}

int Book::getYear() const
{
    return year;
}

string Book::getIsbn() const
{
    return isbn;
}

string Book::getPublisher() const
{
    return publisher;
}

string Book::getCategory() const
{
    return category;
}

Book::Book(string _name, string _author, int _year, string _isbn, string _publisher, string _category, int _copies):
    name{_name}, author{_author}, year{_year}, isbn{_isbn}, publisher{_publisher}, category{_category}, copies{_copies}
{ }
