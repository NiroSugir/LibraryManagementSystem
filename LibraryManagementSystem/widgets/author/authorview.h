#ifndef AUTHORVIEW_H
#define AUTHORVIEW_H

#include <QWidget>
#include <vector>
#include "models/author.h"

namespace Ui {
class AuthorView;
}

using std::vector;
using std::function;

class AuthorView : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorView(QWidget *parent = nullptr);
    ~AuthorView();

    void setEventHandlers(
        function<void (int)> _handleSelectAuthorForEdit
    );

    void updateAuthorsList(vector<Author> authors);
    void selectAuthorForEdit(Author author);

private slots:
    void on_buttonSubmit_clicked();
    void on_buttonReset_clicked();

    void on_tableWidgetAuthors_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::AuthorView *ui;

    void setupAuthorsTable();

    function<void (int)> handleSelectAuthorForEdit;
};

#endif // AUTHORVIEW_H
