#ifndef AUTHORVIEW_H
#define AUTHORVIEW_H

#include <QWidget>
#include <vector>
#include "models/author.h"

namespace Ui {
class AuthorView;
}

using std::vector;

class AuthorView : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorView(QWidget *parent = nullptr);
    ~AuthorView();

//    void setEventHandlers(
//        function<void (string)> _handleSearch,
//        function<void (int)> _handleChangeSelectedBook
//    );

    void updateAuthorsList(vector<Author> authors);
private:
    Ui::AuthorView *ui;

    void setupAuthorsTable();
};

#endif // AUTHORVIEW_H
