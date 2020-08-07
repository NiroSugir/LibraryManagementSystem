#include "bookview.h"
#include "ui_bookview.h"

BookView::BookView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookView)
{
    ui->setupUi(this);

    initialize();
}

BookView::~BookView()
{
    delete ui;
}

void BookView::initialize()
{
    // todo: get data from database
    list.append("Biography");
    list.append("Science-Fiction");
    list.append("Mystery");
    list.append("Fantasy");

    model.setStringList(list);
    ui->listViewCategories->setModel(&model);
}
