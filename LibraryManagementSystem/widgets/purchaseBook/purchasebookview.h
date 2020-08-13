#ifndef PURCHASEBOOKVIEW_H
#define PURCHASEBOOKVIEW_H

#include "models/sellablebook.h"
#include <QWidget>

namespace Ui {
class PurchaseBookView;
}

using std::function;
using std::vector;
using std::string;
using std::to_string;

class PurchaseBookView : public QWidget
{
    Q_OBJECT

public:
    explicit PurchaseBookView(QWidget *parent = nullptr);
    ~PurchaseBookView();

    void initialize(const User *_currentUser, vector<Author> _authors, vector<string> _categories);
    void populateBooksOnSale(vector<SellableBook> _booksForSale);
    void viewSelectedBook(SellableBook book);
    void clearListing();

    void setEventHandlers(
        function<void (SellableBook)> _handlePurchaseBook,
        function<void (int)> _handleChangeSelectedBook
    );

private slots:
    void on_tableWidgetBooksForSale_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::PurchaseBookView *ui;

    const User *currentUser{nullptr};
    vector<Author> authors{};
    vector<string> categories{};

    void setupBooksForSaleTable();
    void popualteAuthors(vector<Author> _authors);
    void populateCategories(vector<string> _categories);

    function<void (SellableBook)> handlePurchaseBook;
    function<void (int)> handleChangeSelectedBook;
};

#endif // PURCHASEBOOKVIEW_H
