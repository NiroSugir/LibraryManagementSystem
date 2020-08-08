#ifndef BOOKVIEW_H
#define BOOKVIEW_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QModelIndex>
#include <vector>

namespace Ui {
class BookView;
}

using std::string;
using std::vector;

class BookView : public QWidget
{
    Q_OBJECT

public:
    explicit BookView(QWidget *parent = nullptr);
    ~BookView();

    void initialize(vector<string> _categories);
    void clearSearchResults();

private:
    Ui::BookView *ui;

    QStringList list;
    // TODO: create a model class and use the MVC pattern
    QStringListModel model;

};

#endif // BOOKVIEW_H
