#include "authormodel.h"

AuthorModel::AuthorModel()
{

}

vector<Author> AuthorModel::getAllDistinctAuthorsFromDb()
{
    DbConnection connection;
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query;

        authors.clear();
        selectedAuthor = nullptr;

        const bool successfullyPrepared = query.prepare("select author_id, first_name, last_name from Authors");

        if (successfullyPrepared) {
            query.exec();

            if (query.lastError().isValid()) {
                db.close();

                throw "Something went wrong, please try again later.";
            } else {
                while(query.next()) {
                    authors.push_back(Author{
                        // id
                        query.value(0).toString().toStdString(),
                        // first name
                        query.value(1).toString().toStdString(),
                        // last name
                        query.value(2).toString().toStdString(),
                    });
                }

                db.close();
                return authors;
            }
        } else {
            query.clear();
            db.close();
            throw "Something went wrong, please try again later.";
        }

        query.clear();
        db.close();
    } else {
        throw "Internal DB Error! Could not access database. Please wait a while and try again. If problem persists, reinstall the app or call at 1-800-SHOULD-HAVE-PAID-FOR-SUPPORT ext. HAHA";
    }
}

vector<Author> AuthorModel::getAllLocalAuthors()
{
    return authors;
}

Author AuthorModel::selectAuthorAtIndex(int index)
{
    selectedAuthor = &authors[index];

    return *selectedAuthor;
}

Author AuthorModel::createNewAuthor()
{
    authors.push_back(Author{"","",""});
    selectedAuthor = &authors[authors.size() - 1];

    return *selectedAuthor;
}

void AuthorModel::saveChanges(string firstName, string lastName)
{
    DbConnection connection;
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query;

        if (selectedAuthor->getId() == "") {
            // insert author to db
            query.prepare("insert into Authors (first_name, last_name) values (:first_name, :last_name)");

        } else {
            // update author in db
            query.prepare("update Authors set first_name = :first_name,  last_name = :last_name where author_id = :author_id");
            query.bindValue(":author_id", selectedAuthor->getId().c_str());
        }

        query.bindValue(":first_name", firstName.c_str());
        query.bindValue(":last_name", lastName.c_str());

        query.exec();
    }
    db.close();
}
