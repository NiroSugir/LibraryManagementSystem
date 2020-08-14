#ifndef BOOKVIEW_H
#define BOOKVIEW_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QModelIndex>
#include <vector>
#include "models/borrowablebook.h"
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
        function<void ()> _handleRetrieveCategories,
        function<void ()> _handleBorrowBook
    );
    void populateCategories(vector<string> _categories);
    void clearSearchResults();
    void updateSearchResults(const vector<BorrowableBook> &books);
    void viewSelectedBook(const BorrowableBook &book);
    void clearSelectedBook();

private slots:
    void on_pushButtonSearch_clicked();
    void on_tableWidgetSearchResults_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_lineEditSearch_returnPressed();
    void on_pushButtonBorrow_clicked();

private:
    Ui::BookView *ui;

    vector<string> categories;
    void setupSearchResultsTable();
    void search();
    const User *currentUser{nullptr};
    void setBookInfoEditable(bool editable);
    void setBookBorrowabilityAndAvailabilityDisplay();
    void setBookAvailabilityForBorrowing(const BorrowableBook &book);

    function<void (string)> handleSearch;
    function<void (int)> handleChangeSelectedBook;
    function<void ()> handleRetrieveCategories;
    function<void ()> handleBorrowBook;
};

#endif // BOOKVIEW_H
