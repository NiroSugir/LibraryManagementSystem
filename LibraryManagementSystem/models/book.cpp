#include "book.h"

Book::Book(string _isbn, string _name, Author _author, int _year, string _category):
    isbn{_isbn}, name{_name}, author{_author}, year{_year}, category{_category}
{

}

string Book::getName() const
{
    return name;
}

string Book::getAuthorName() const
{
    return author.getFirstName() + " " + author.getLastName();
}

int Book::getYear() const
{
    return year;
}

Author Book::getAuthor() const
{
    return author;
}

string Book::getIsbn() const
{
    return isbn;
}

string Book::getCategory() const
{
    return category;
}
