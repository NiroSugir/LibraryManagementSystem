#include "supplierhomeview.h"
#include "ui_supplierhomeview.h"

SupplierHomeView::SupplierHomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierHomeView)
{
    ui->setupUi(this);
}

SupplierHomeView::~SupplierHomeView()
{
    delete ui;
}
