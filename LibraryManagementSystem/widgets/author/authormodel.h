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

    Author selectAuthorAtIndex(int index);
};

#endif // AUTHORMODEL_H
