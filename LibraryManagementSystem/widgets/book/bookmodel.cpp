#include "bookmodel.h"

BookModel::~BookModel()
{
    delete selectedBook;
    selectedBook = nullptr;
}

vector<Book> BookModel::keywordSearch(string searchString)
{
    vector<Book> books;

    // TODO: search the db

    // TODO: remove PLACEHOLDER
    books.push_back(Book{"Fellowship of the Ring", "J.R.R. Tolkien", 1948, "some-isbn", "Some Publisher", "Fantasy"});
    books.push_back(Book{"The Two Towers", "J.R.R. Tolkien", 1950, "some-isbn", "Some Publisher", "Fantasy"});
    books.push_back(Book{"1984", "George Orwell", 1945, "some-other-isbn", "Some Other Publisher", "Science-Fiction"});

    // save the search results in the model and pass the results to the caller
    visibleBooks = books;

    return books;
}

//const Book& BookModel::getBook(const string &_isbn)
//{
//    return Book{"Fellowship of the Ring", "J.R.R. Tolkien", 1948, "some-isbn", "Some Publisher", "Fantasy"};
//}


const Book& BookModel::getBook(const int &selectedBookIndex)
{
    selectedBook = &visibleBooks[selectedBookIndex];
    return *selectedBook;
}
