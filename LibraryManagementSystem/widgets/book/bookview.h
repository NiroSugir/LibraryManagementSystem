#ifndef BOOKVIEW_H
#define BOOKVIEW_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QModelIndex>

namespace Ui {
class BookView;
}

class BookView : public QWidget
{
    Q_OBJECT

public:
    explicit BookView(QWidget *parent = nullptr);
    ~BookView();

private:
    Ui::BookView *ui;

    QStringList list;
    // TODO: create a model class and use the MVC pattern
    QStringListModel model;

    void initialize();
};

#endif // BOOKVIEW_H
