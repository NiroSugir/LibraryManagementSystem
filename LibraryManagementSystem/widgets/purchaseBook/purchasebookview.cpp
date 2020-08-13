#include "purchasebookview.h"
#include "ui_purchasebookview.h"

#include <QDebug>

PurchaseBookView::PurchaseBookView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PurchaseBookView)
{
    ui->setupUi(this);
    setupBooksForSaleTable();
}

PurchaseBookView::~PurchaseBookView()
{
    delete ui;

    if (currentBook) {
        delete currentBook;
        currentBook = nullptr;
    }
}

void PurchaseBookView::initialize(const User *_currentUser, vector<Author> _authors, vector<string> _categories)
{
    currentUser = _currentUser;
    popualteAuthors(_authors);
    populateCategories(_categories);
}

void PurchaseBookView::populateBooksOnSale(vector<SellableBook> _booksForSale)
{
    ui->tableWidgetBooksForSale->clearContents();
    ui->tableWidgetBooksForSale->setRowCount(_booksForSale.size());

    unsigned int row = 0;
    for (const SellableBook &book: _booksForSale) {
        // remove the extra zeros from the double for $
        string dollars = to_string(((int) (book.getPrice() * 100) - ((int)(book.getPrice() * 100) % 100)) / 100);
        string cents = to_string((int)(book.getPrice() * 100) % 100);

        QString title{QString::fromStdString(book.getName())};
        QString author{QString::fromStdString(book.getAuthor().getLastName() + ", " + book.getAuthor().getFirstName())};
        QString price{("$" + dollars + "." + cents).c_str()};

        ui->tableWidgetBooksForSale->setItem(row, 0, new QTableWidgetItem{title});
        ui->tableWidgetBooksForSale->setItem(row, 1, new QTableWidgetItem{author});
        ui->tableWidgetBooksForSale->setItem(row, 2, new QTableWidgetItem{price});

        row++;
    }
}

void PurchaseBookView::viewSelectedBook(SellableBook book)
{
    currentBook = new SellableBook{book};

    ui->lineEditTitle->setText(QString::fromStdString(book.getName()));
    ui->lineEditYear->setText(QString::fromStdString(to_string(book.getYear())));
    ui->lineEditIsbn->setText(QString::fromStdString(book.getIsbn()));
    ui->doubleSpinBoxPrice->setValue(book.getPrice());

    int authorIndex;
    string authorName = book.getAuthor().getLastName() + ", " + book.getAuthor().getFirstName();
    for (const Author &thisAuthor : authors) {
        string thisAuthorName = thisAuthor.getLastName() + ", " + thisAuthor.getFirstName();

        if (thisAuthorName == authorName) {
            break;
        }

        authorIndex++;
    }

    ui->comboBoxAuthors->setCurrentIndex(authorIndex);

    const string thisCategory = book.getCategory();

    int row = 0;
    for(const string &category : categories) {
        if (category == thisCategory) {
            ui->listViewCategories->item(row)->setSelected(true);
        } else {
            ui->listViewCategories->item(row)->setSelected(false);
        }

        row++;
    }

    ui->buttonPurchaseBook->setEnabled(true);
}

void PurchaseBookView::clearListing()
{
    ui->lineEditIsbn->clear();
    ui->lineEditTitle->clear();
    ui->comboBoxAuthors->clear();
    ui->lineEditYear->clear();
    ui->listViewCategories->clear();
    ui->doubleSpinBoxPrice->setValue(0.00);
    ui->buttonPurchaseBook->setEnabled(false);

    currentBook = nullptr;
}

void PurchaseBookView::setEventHandlers(function<void (SellableBook)> _handlePurchaseBook, function<void (int)> _handleChangeSelectedBook)
{
    handlePurchaseBook = _handlePurchaseBook;
    handleChangeSelectedBook = _handleChangeSelectedBook;
}

void PurchaseBookView::setupBooksForSaleTable()
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

void PurchaseBookView::popualteAuthors(vector<Author> _authors)
{
    authors = _authors;

    for (const auto &_author: authors) {
        ui->comboBoxAuthors->addItem((_author.getFirstName() + " " + _author.getLastName()).c_str());
    }
}

void PurchaseBookView::populateCategories(vector<string> _categories)
{
    categories = _categories;

    for (const string &category: _categories) {
        ui->listViewCategories->addItem(category.c_str());
    }
}

void PurchaseBookView::on_tableWidgetBooksForSale_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    // book changes only if the row changes
    if (currentRow != previousRow && currentRow > -1) {
        // handle change book view
        handleChangeSelectedBook(currentRow);
    }
}

void PurchaseBookView::on_buttonPurchaseBook_clicked()
{
    if (!currentBook) {
        qDebug() << "This path should not exist. Attempting to purchase an unselected book";
        return;
    }

    handlePurchaseBook(*currentBook);
    currentBook = nullptr;
}
