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

void BookView::initialize(vector<string> *_categories)
{
    setupSearchResultsTable();

    for (const string &category: *_categories) {
        ui->listViewCategories->addItem(QString::fromStdString(category));
    }
}

void BookView::setupSearchResultsTable()
{
    // force the columns to occupy the whole table width
    ui->tableWidgetSearchResults->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetSearchResults->setColumnCount(2);
    ui->tableWidgetSearchResults->setRowCount(0);
    ui->tableWidgetSearchResults->setHorizontalHeaderLabels(QStringList{
        QString{"Title"},
        QString{"Author"}
    });
}
