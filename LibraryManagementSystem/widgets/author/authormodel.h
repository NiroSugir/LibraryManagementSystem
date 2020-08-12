#ifndef AUTHORMODEL_H
#define AUTHORMODEL_H

#include "models/author.h"
#include <vector>
#include "dbconnection.h"

using std::vector;
using std::string;

class AuthorModel
{
private:
    DbConnection connection;

    vector<Author> authors{};

    Author *selectedAuthor{nullptr};

public:
    AuthorModel();

    vector<Author> getAllDistinctAuthorsFromDb();
    vector<Author> getAllLocalAuthors();

    Author selectAuthorAtIndex(int index);
    Author createNewAuthor();
    void saveChanges(string firstName, string lastName);
};

#endif // AUTHORMODEL_H
