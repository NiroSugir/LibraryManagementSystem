#include "authorview.h"
#include "ui_authorview.h"

#include <QDebug>

AuthorView::AuthorView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorView)
{
    ui->setupUi(this);

    setupAuthorsTable();
}

AuthorView::~AuthorView()
{
    if (ui) delete ui;
}

void AuthorView::updateAuthorsList(vector<Author> authors)
{
    ui->tableWidgetAuthors->clearContents();
    ui->tableWidgetAuthors->setRowCount(authors.size());
    qDebug() << "num authors: " << authors.size();

    int row = 0;
    for (auto const &author: authors) {
        QString firstName{QString::fromStdString(author.getFirstName())};
        QString lastName{QString::fromStdString(author.getLastName())};

        ui->tableWidgetAuthors->setItem(row, 0, new QTableWidgetItem{firstName});
        ui->tableWidgetAuthors->setItem(row, 1, new QTableWidgetItem{lastName});

        row++;
    }
}

void AuthorView::setupAuthorsTable()
{
    // force the columns to occupy the whole table width
    ui->tableWidgetAuthors->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetAuthors->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidgetAuthors->setColumnCount(2);
    ui->tableWidgetAuthors->setRowCount(0);
    ui->tableWidgetAuthors->setHorizontalHeaderLabels(QStringList{
        QString{"First Name"},
        QString{"Last Name"}
    });
}
