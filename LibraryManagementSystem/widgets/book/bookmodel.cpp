#include "bookmodel.h"

BookModel::BookModel()
{

}

vector<Book> BookModel::keywordSearch(string searchString)
{
    vector<Book> books;

    // TODO: search the db

    // TODO: remove PLACEHOLDER
    books.push_back(Book{"Fellowship of the Ring", "J.R.R. Tolkien", 1948, "some-isbn", "Some Publisher", "Fantasy"});
    books.push_back(Book{"The Two Towers", "J.R.R. Tolkien", 1950, "some-isbn", "Some Publisher", "Fantasy"});
    books.push_back(Book{"1984", "George Orwell", 1945, "some-other-isbn", "Some Other Publisher", "Science-Fiction"});

    return books;
}

Book BookModel::getBook(string _isbn)
{
    return Book{"Fellowship of the Ring", "J.R.R. Tolkien", 1948, "some-isbn", "Some Publisher", "Fantasy"};
}