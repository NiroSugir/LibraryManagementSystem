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
        function<void (int)> _handleSelectAuthorForEdit,
        function<int (void)> _handleCreateNewAuthor,
        function<void (string, string)> _handleSaveChanges
    );

    void updateAuthorsList(vector<Author> authors);
    void selectAuthorForEdit(Author author);

private slots:
    void on_buttonEditAuthor_clicked();
    void on_buttonReset_clicked();
    void on_tableWidgetAuthors_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_pushButtonCreateAuthor_clicked();


private:
    Ui::AuthorView *ui;

    void setupAuthorsTable();

    function<void (int)> handleSelectAuthorForEdit;
    function<int (void)> handleCreateNewAuthor;
    function<void (string, string)> handleSaveChanges;
    bool createMode{false};
};

#endif // AUTHORVIEW_H
