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
using std::vector;
using std::function;

struct BookInfo{

};

class BookView : public QWidget
{
    Q_OBJECT

public:
    explicit BookView(QWidget *parent = nullptr);
    ~BookView();

    void initialize(vector<string> *_categories);
    void setEventHandlers(function<void (std::string)> _handleSearch);
    void clearSearchResults();
    void updateSearchResults(const vector<Book> &books);

private slots:
    void on_pushButtonSearch_clicked();

private:
    Ui::BookView *ui;

    void setupSearchResultsTable();
    std::function<void (std::string)> handleSearch;
};

#endif // BOOKVIEW_H
