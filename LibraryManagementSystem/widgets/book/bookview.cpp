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

    setBookBorrowabilityAndAvailabilityDisplay();
}

void BookView::setEventHandlers(
        function<void (string)> _handleSearch,
        function<void (int)> _handleChangeSelectedBook,
        function<void ()> _handleRetrieveCategories,
        function<void ()> _handleBorrowBook
) {
    handleSearch = _handleSearch;
    handleChangeSelectedBook = _handleChangeSelectedBook;
    handleRetrieveCategories = _handleRetrieveCategories;
    handleBorrowBook = _handleBorrowBook;
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

void BookView::updateSearchResults(const vector<BorrowableBook> &books)
{
    ui->tableWidgetSearchResults->clearContents();
    ui->tableWidgetSearchResults->setRowCount(books.size());

    int row = 0;
    for (auto const &book: books) {
        QString title{QString::fromStdString(book.getName())};
        QString author{QString::fromStdString(book.getAuthorName())};

        auto itemTitle = new QTableWidgetItem{title};
        auto itemAuthor = new QTableWidgetItem{author};
        auto itemStatus = new QTableWidgetItem{book.getBorrowedBy() == "" ? "Available" : "Unavailable"};

        // colour code the rows based on book availability
        auto rowColour = book.getBorrowedBy() == "" ? QColor(80, 220, 100, 30) : QColor(250, 128, 114, 60);
        itemStatus->setBackgroundColor(rowColour);
        itemAuthor->setBackgroundColor(rowColour);
        itemTitle->setBackgroundColor(rowColour);

        ui->tableWidgetSearchResults->setItem(row, 0, itemTitle);
        ui->tableWidgetSearchResults->setItem(row, 1, itemAuthor);
        ui->tableWidgetSearchResults->setItem(row, 2, itemStatus);


        row++;
    }
}

void BookView::viewSelectedBook(const BorrowableBook &book)
{
    ui->lineEditTitle->setText(QString::fromStdString(book.getName()));
    ui->lineEditAuthor->setText(QString::fromStdString(book.getAuthorName()));
    ui->lineEditYear->setText(QString::fromStdString(to_string(book.getYear())));
    ui->lineEditIsbn->setText(QString::fromStdString(book.getIsbn()));

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

    setBookAvailabilityForBorrowing(book);
}

void BookView::clearSelectedBook()
{
    ui->lineEditTitle->setText("");
    ui->lineEditAuthor->setText("");
    ui->lineEditYear->setText("");
    ui->lineEditIsbn->setText("");
    ui->pushButtonBorrow->setDisabled(true);

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

    ui->tableWidgetSearchResults->setColumnCount(3);
    ui->tableWidgetSearchResults->setRowCount(0);
    ui->tableWidgetSearchResults->setHorizontalHeaderLabels(QStringList{
        QString{"Title"},
        QString{"Author"},
        QString{"Status"}
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

    if (!editable){
        // make it appear enabled, but a quick way to disable selection change for
        // list ui elements
        ui->listViewCategories->setEnabled(editable);
        ui->listViewCategories->setStyleSheet("background-color: white; color: black;");
    }
}

void BookView::setBookBorrowabilityAndAvailabilityDisplay()
{
    ui->labelAvailable->setVisible(true);
    ui->labelAvailability->setVisible(true);

    // borrow button is visible to library members only
    // this does not guarantee the user can borrow, only that the button
    // is visible. if the user's not in a good standing (has borrowed too many
    // books already or has to pay fine), they wont be able to click on it
    // TODO: disable button (but keep it visible) if they can't borrow. tooltip
    // should hint towards the reason
    ui->pushButtonBorrow->setVisible(currentUser && currentUser->getRole() == Role::Member && currentUser->isValidated());

}

void BookView::setBookAvailabilityForBorrowing(const BorrowableBook &book)
{
    ui->pushButtonBorrow->setVisible(currentUser && currentUser->getRole() == Role::Member && currentUser->isValidated());
    ui->pushButtonBorrow->setEnabled(book.getBorrowedBy() == "");
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

void BookView::on_pushButtonBorrow_clicked()
{
    handleBorrowBook();
}
