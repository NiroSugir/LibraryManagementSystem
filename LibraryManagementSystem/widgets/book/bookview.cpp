#include "bookview.h"
#include "ui_bookview.h"

BookView::BookView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookView)
{
    ui->setupUi(this);

    setupSearchResultsTable();
}

BookView::~BookView()
{
    delete ui;
}

void BookView::initialize(vector<string> *_categories)
{
    for (const string &category: *_categories) {
        ui->listViewCategories->addItem(QString::fromStdString(category));
    }
}

void BookView::setupSearchResultsTable()
{
    QHeaderView* header = ui->tableWidgetSearchResults->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetSearchResults->setColumnCount(2);
    ui->tableWidgetSearchResults->setRowCount(0);
    ui->tableWidgetSearchResults->setHorizontalHeaderLabels(QStringList{
        QString{"Title"},
        QString{"Author"}
//        QString{"Year"}
    });
}

