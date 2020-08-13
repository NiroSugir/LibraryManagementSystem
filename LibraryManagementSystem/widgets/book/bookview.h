#ifndef BOOKVIEW_H
#define BOOKVIEW_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QModelIndex>
#include <vector>
#include "models/book.h"
#include "models/user.h"
#include <QMessageBox>

namespace Ui {
class BookView;
}

using std::string;
using std::to_string;
using std::vector;
using std::function;

class BookView : public QWidget
{
    Q_OBJECT

public:
    explicit BookView(QWidget *parent = nullptr);
    ~BookView();

    void initialize(const User *_currentUser);
    void setEventHandlers(
        function<void (string)> _handleSearch,
        function<void (int)> _handleChangeSelectedBook,
        function<void ()> _handleRetrieveCategories
    );
    void populateCategories(vector<string> _categories);
    void clearSearchResults();
    void updateSearchResults(const vector<Book> &books);
    void viewSelectedBook(const Book &book);
    void clearSelectedBook();

private slots:
    void on_pushButtonSearch_clicked();
    void on_tableWidgetSearchResults_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_lineEditSearch_returnPressed();

private:
    Ui::BookView *ui;

    vector<string> categories;
    void setupSearchResultsTable();
    void search();
    const User *currentUser{nullptr};
    void setBookInfoEditable(bool editable);

    function<void (string)> handleSearch;
    function<void (int)> handleChangeSelectedBook;
    function<void ()> handleRetrieveCategories;
};

#endif // BOOKVIEW_H
