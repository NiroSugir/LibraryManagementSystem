#ifndef BOOKVIEW_H
#define BOOKVIEW_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QModelIndex>
#include <vector>
#include "models/book.h"

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

    void initialize(vector<string> &_categories);
    void setEventHandlers(
        function<void (string)> _handleSearch,
        function<void (int)> _handleChangeSelectedBook
    );
    void clearSearchResults();
    void updateSearchResults(const vector<Book> &books);
    void viewSelectedBook(const Book &book);

private slots:
    void on_pushButtonSearch_clicked();
    void on_tableWidgetSearchResults_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::BookView *ui;

    void setupSearchResultsTable();

    function<void (string)> handleSearch;
    function<void (int)> handleChangeSelectedBook;
};

#endif // BOOKVIEW_H
