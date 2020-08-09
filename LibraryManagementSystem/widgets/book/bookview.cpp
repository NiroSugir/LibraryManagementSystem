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

void BookView::setEventHandlers(function<void (std::string)> _handleSearch)
{
    handleSearch = _handleSearch;
}

void BookView::updateSearchResults(const vector<Book> &books)
{
    ui->tableWidgetSearchResults->clearContents();
    ui->tableWidgetSearchResults->setRowCount(books.size());

    int row = 0;
    for (auto const &book: books) {
        QString title{QString::fromStdString(book.getName())};
        QString author{QString::fromStdString(book.getAuthor())};

        ui->tableWidgetSearchResults->setItem(row, 0, new QTableWidgetItem{title});
        ui->tableWidgetSearchResults->setItem(row, 1, new QTableWidgetItem{author});

        row++;
    }
}

void BookView::setupSearchResultsTable()
{
    // force the columns to occupy the whole table width
    ui->tableWidgetSearchResults->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetSearchResults->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidgetSearchResults->setColumnCount(2);
    ui->tableWidgetSearchResults->setRowCount(0);
    ui->tableWidgetSearchResults->setHorizontalHeaderLabels(QStringList{
        QString{"Title"},
        QString{"Author"}
    });
}

void BookView::on_pushButtonSearch_clicked()
{
    handleSearch(ui->lineEditSearch->text().toStdString());
}
