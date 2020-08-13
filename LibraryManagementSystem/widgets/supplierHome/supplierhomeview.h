#ifndef SUPPLIERHOMEVIEW_H
#define SUPPLIERHOMEVIEW_H

#include "models/sellablebook.h"
#include <QWidget>

namespace Ui {
class SupplierHomeView;
}

using std::function;
using std::vector;
using std::string;

class SupplierHomeView : public QWidget
{
    Q_OBJECT

public:
    explicit SupplierHomeView(QWidget *parent = nullptr);
    ~SupplierHomeView();

    void initialize(const User *_currentUser, vector<Author> _authors, vector<string> _categories);
    void populateBooksOnSaleBySupplier(vector<SellableBook> _booksForSale);
    void clearListing();

    void setEventHandlers(
        function<void (SellableBook)> _handleListBookForSale
    );

private slots:
    void on_buttonSellBook_clicked();

private:
    Ui::SupplierHomeView *ui;

    const User *currentUser{nullptr};
    vector<Author> authors{};
    vector<string> categories{};

    void setupBooksForSaleTable();
    void popualteAuthors(vector<Author> _authors);
    void populateCategories(vector<string> _categories);

    function<void (SellableBook)> handleListBookForSale;
};

#endif // SUPPLIERHOMEVIEW_H
