#include "authormodel.h"

AuthorModel::AuthorModel()
{

}

vector<Author> AuthorModel::getAllDistinctAuthorsFromDb()
{
    QSqlDatabase db = connection.getDb();

    db.open();
    if (db.isOpen()) {
        QSqlQuery query;

        authors.clear();
        selectedAuthor = nullptr;

        // TODO: replace prepared statement with a straight query
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

            // TODO: log: "failed to prepare statement"
            throw "Something went wrong, please try again later.";
        }

        query.clear();
        db.close();
    } else {
        // TODO: log: "failed to open db"
        throw "Internal DB Error! Could not access database. Please wait a while and try again. If problem persists, reinstall the app or call at 1-800-SHOULD-HAVE-PAID-FOR-SUPPORT ext. HAHA";
    }
}

Author AuthorModel::selectAuthorAtIndex(int index)
{
    selectedAuthor = &authors[index];

    return *selectedAuthor;
}
