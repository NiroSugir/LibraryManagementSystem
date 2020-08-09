#include "bookmodel.h"

BookModel::~BookModel()
{
    delete selectedBook;
    selectedBook = nullptr;
}

vector<Book> BookModel::keywordSearch(string searchString)
{
    visibleBooks.clear();

    // TODO: search the db

    // TODO: remove PLACEHOLDER
    visibleBooks.push_back(Book{"Fellowship of the Ring", "J.R.R. Tolkien", 1948, "some-isbn", "Some Publisher", "Fantasy"});
    visibleBooks.push_back(Book{"The Two Towers", "J.R.R. Tolkien", 1950, "some-isbn", "Some Publisher", "Fantasy"});
    visibleBooks.push_back(Book{"1984", "George Orwell", 1945, "some-other-isbn", "Some Other Publisher", "Science-Fiction"});

    // save the search results in the model and pass the results to the caller

    return visibleBooks;
}

//const Book& BookModel::getBook(const string &_isbn)
//{
//    return Book{"Fellowship of the Ring", "J.R.R. Tolkien", 1948, "some-isbn", "Some Publisher", "Fantasy"};
//}


Book BookModel::getBook(const int &selectedBookIndex)
{
    selectedBook = &visibleBooks[selectedBookIndex];
    return *selectedBook;
}
