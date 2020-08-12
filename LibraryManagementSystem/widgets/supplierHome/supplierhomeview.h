#ifndef SUPPLIERHOMEVIEW_H
#define SUPPLIERHOMEVIEW_H

#include <QWidget>

namespace Ui {
class SupplierHomeView;
}

class SupplierHomeView : public QWidget
{
    Q_OBJECT

public:
    explicit SupplierHomeView(QWidget *parent = nullptr);
    ~SupplierHomeView();

private:
    Ui::SupplierHomeView *ui;
};

#endif // SUPPLIERHOMEVIEW_H
