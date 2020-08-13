#include "supplierhomeview.h"
#include "ui_supplierhomeview.h"

#include <QDebug>

SupplierHomeView::SupplierHomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierHomeView)
{
    ui->setupUi(this);

    setupBooksForSaleTable();
    ui->doubleSpinBoxPrice->setValue(15.00);
}

SupplierHomeView::~SupplierHomeView()
{
    delete ui;
}

void SupplierHomeView::initialize(const User *_currentUser, vector<Author> _authors, vector<string> _categories)
{
    currentUser = _currentUser;
    popualteAuthors(_authors);
    populateCategories(_categories);
}

void SupplierHomeView::populateBooksOnSaleBySupplier(vector<SellableBook> _booksForSale)
{
    // todo: clear table


    ui->tableWidgetBooksForSale->clearContents();
    ui->tableWidgetBooksForSale->setRowCount(_booksForSale.size());

    unsigned int row = 0;
    for (const SellableBook &book: _booksForSale) {
        QString title{QString::fromStdString(book.getName())};
        QString author{QString::fromStdString(book.getAuthor().getLastName() + ", " + book.getAuthor().getFirstName())};
        QString price{
            ("$" + std::to_string(book.getPrice())).c_str()
        };

        ui->tableWidgetBooksForSale->setItem(row, 0, new QTableWidgetItem{title});
        ui->tableWidgetBooksForSale->setItem(row, 1, new QTableWidgetItem{author});
        ui->tableWidgetBooksForSale->setItem(row, 2, new QTableWidgetItem{price});

        row++;
    }
}

void SupplierHomeView::setEventHandlers(function<void (SellableBook)> _handleListBookForSale)
{
    handleListBookForSale = _handleListBookForSale;
}

void SupplierHomeView::on_buttonSellBook_clicked()
{
    SellableBook book {
        ui->lineEditIsbn->text().toStdString().c_str(),
        ui->lineEditTitle->text().toStdString().c_str(),
        {authors[ui->comboBoxAuthors->currentIndex()]},
        ui->lineEditYear->text().toInt(),
        categories[ui->listViewCategories->currentIndex().row()],
        *currentUser,
        ui->doubleSpinBoxPrice->value()
    };

    handleListBookForSale(book);
}

void SupplierHomeView::setupBooksForSaleTable()
{
    // force the columns to occupy the whole table width
    ui->tableWidgetBooksForSale->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetBooksForSale->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidgetBooksForSale->setColumnCount(3);
    ui->tableWidgetBooksForSale->setRowCount(0);
    ui->tableWidgetBooksForSale->setHorizontalHeaderLabels(QStringList{
        QString{"Title"},
        QString{"Author"},
        QString{"Price"}
    });
}

void SupplierHomeView::popualteAuthors(vector<Author> _authors)
{
    authors = _authors;

    for (const auto &_author: authors) {
        ui->comboBoxAuthors->addItem((_author.getFirstName() + " " + _author.getLastName()).c_str());
    }
}

void SupplierHomeView::populateCategories(vector<string> _categories)
{
    categories = _categories;

    for (const string &category: _categories) {
        ui->listViewCategories->addItem(category.c_str());
    }
}
