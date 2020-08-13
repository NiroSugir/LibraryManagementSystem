#include "supplierhomeview.h"
#include "ui_supplierhomeview.h"

#include <QDebug>

SupplierHomeView::SupplierHomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierHomeView)
{
    ui->setupUi(this);

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
