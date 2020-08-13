#include "bookview.h"
#include "ui_bookview.h"
#include <QDebug>
#include "models/role.h"

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

void BookView::initialize(const User *_currentUser)
{
    currentUser = _currentUser;

    setupSearchResultsTable();
    handleRetrieveCategories();

    // setup what user can do with books (edit/borrow)
    setBookInfoEditable(_currentUser && _currentUser->getRole() == Role::Staff && _currentUser->isValidated());
}

void BookView::setEventHandlers(
        function<void (string)> _handleSearch,
        function<void (int)> _handleChangeSelectedBook,
        function<void ()> _handleRetrieveCategories
) {
    handleSearch = _handleSearch;
    handleChangeSelectedBook = _handleChangeSelectedBook;
    handleRetrieveCategories = _handleRetrieveCategories;
}

void BookView::populateCategories(vector<string> _categories)
{
    categories = _categories;

    for (const string &category: categories) {
        ui->listViewCategories->addItem(QString::fromStdString(category));
    }
}

void BookView::clearSearchResults()
{

}

void BookView::updateSearchResults(const vector<Book> &books)
{
    ui->tableWidgetSearchResults->clearContents();
    ui->tableWidgetSearchResults->setRowCount(books.size());
    qDebug() << "num books: " << books.size();

    int row = 0;
    for (auto const &book: books) {
        QString title{QString::fromStdString(book.getName())};
        QString author{QString::fromStdString(book.getAuthor())};

        ui->tableWidgetSearchResults->setItem(row, 0, new QTableWidgetItem{title});
        ui->tableWidgetSearchResults->setItem(row, 1, new QTableWidgetItem{author});

        row++;
    }
}

void BookView::viewSelectedBook(const Book &book)
{
    ui->lineEditTitle->setText(QString::fromStdString(book.getName()));
    ui->lineEditAuthor->setText(QString::fromStdString(book.getAuthor()));
    ui->lineEditYear->setText(QString::fromStdString(to_string(book.getYear())));
    ui->lineEditIsbn->setText(QString::fromStdString(book.getIsbn()));
    ui->lineEditPublisher->setText(QString::fromStdString(book.getPublisher()));

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

}

void BookView::clearSelectedBook()
{
    ui->lineEditTitle->setText("");
    ui->lineEditAuthor->setText("");
    ui->lineEditYear->setText("");
    ui->lineEditIsbn->setText("");
    ui->lineEditPublisher->setText("");

    for(unsigned int row = 0; row < categories.size(); row++) {
        ui->listViewCategories->item(row)->setSelected(false);
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

void BookView::search()
{
    clearSelectedBook();

    try {
        handleSearch(ui->lineEditSearch->text().toStdString());
    } catch (const char* errorMsg) {
        // show an alert box with the error message
        QMessageBox alert;
        alert.setWindowTitle("Search Error!");
        alert.setText(errorMsg);
        alert.setIcon(QMessageBox::Critical);
        alert.setStandardButtons(QMessageBox::Ok);
        alert.setDefaultButton(QMessageBox::Ok);

        alert.exec();
    }
}

void BookView::setBookInfoEditable(bool editable)
{
    ui->lineEditIsbn->setReadOnly(!editable);
    ui->lineEditYear->setReadOnly(!editable);
    ui->lineEditTitle->setReadOnly(!editable);
    ui->lineEditAuthor->setReadOnly(!editable);
    ui->lineEditPublisher->setReadOnly(!editable);

    if (!editable){
        // make it appear enabled, but a quick way to disable selection change for
        // list ui elements
        ui->listViewCategories->setEnabled(editable);
        ui->listViewCategories->setStyleSheet("background-color: white; color: black;");
    }
}

void BookView::on_pushButtonSearch_clicked()
{
    search();
}

void BookView::on_tableWidgetSearchResults_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    // book changes only if the row changes
    if (currentRow != previousRow && currentRow > -1) {
        // handle change book view
        handleChangeSelectedBook(currentRow);
    }
}

void BookView::on_lineEditSearch_returnPressed()
{
    search();
}
