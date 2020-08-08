#include "bookview.h"
#include "ui_bookview.h"

BookView::BookView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookView)
{
    ui->setupUi(this);
}

BookView::~BookView()
{
    delete ui;
}

void BookView::initialize(vector<string> _categories)
{
    for (const string &category: _categories){
        ui->listViewCategories->addItem(QString::fromStdString(category));
    }

    // todo: get data from database
    // list.append("Biography");
    // list.append("Science-Fiction");
    // list.append("Mystery");
    // list.append("Fantasy");

//    model.setStringList(list);
//    ui->listViewCategories->setModel(&model);
}

