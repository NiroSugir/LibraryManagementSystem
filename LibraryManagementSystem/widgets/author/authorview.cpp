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

void AuthorView::setEventHandlers(
    function<void (int)> _handleSelectAuthorForEdit,
    function<int (void)> _handleCreateNewAuthor,
    function<void (string, string)> _handleSaveChanges
) {
    handleSelectAuthorForEdit = _handleSelectAuthorForEdit;
    handleCreateNewAuthor = _handleCreateNewAuthor;
    handleSaveChanges = _handleSaveChanges;
}

void AuthorView::updateAuthorsList(vector<Author> authors)
{
    ui->tableWidgetAuthors->clearContents();
    ui->tableWidgetAuthors->setRowCount(authors.size());

    int row = 0;
    for (auto const &author: authors) {
        QString firstName{QString::fromStdString(author.getFirstName().size() == 0 ? "[new author]" : author.getFirstName())};
        QString lastName{QString::fromStdString(author.getLastName())};

        ui->tableWidgetAuthors->setItem(row, 0, new QTableWidgetItem{firstName});
        ui->tableWidgetAuthors->setItem(row, 1, new QTableWidgetItem{lastName});

        row++;
    }
}

void AuthorView::selectAuthorForEdit(Author author)
{
    ui->groupBox->setEnabled(true);
    ui->lineEditFirstName->setText(author.getFirstName().c_str());
    ui->lineEditLastName->setText(author.getLastName().c_str());
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

void AuthorView::on_buttonReset_clicked()
{

    if (createMode && ui->tableWidgetAuthors->currentIndex().row() == (ui->tableWidgetAuthors->rowCount() - 1)) {
        // adding new author, so reset the fields
        ui->lineEditLastName->clear();
        ui->lineEditFirstName->clear();
    } else {
        // editing author, get the current author data from the db
        handleSelectAuthorForEdit(ui->tableWidgetAuthors->currentIndex().row());
    }

    ui->lineEditFirstName->setFocus();
}

void AuthorView::on_tableWidgetAuthors_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if (currentRow != previousRow && currentRow > -1) {
        // handle change book view
        handleSelectAuthorForEdit(currentRow);
    }
}

void AuthorView::on_pushButtonCreateAuthor_clicked()
{
    // create only one author at a time
    if (createMode) {
        return;
    }

    createMode = true;
    int authorIndex = handleCreateNewAuthor();
    ui->tableWidgetAuthors->item(authorIndex, 0)->setSelected(true);
    ui->tableWidgetAuthors->setCurrentCell(authorIndex, 0);
    ui->lineEditFirstName->setFocus();
}

void AuthorView::on_buttonEditAuthor_clicked()
{
    try {
        if (ui->lineEditLastName->text().size() == 0 || ui->lineEditFirstName->text().size() == 0) {
            ui->lineEditFirstName->setFocus();
            return;
        }

        handleSaveChanges(
            ui->lineEditFirstName->text().toStdString(),
            ui->lineEditLastName->text().toStdString()
        );

        // not editing, but adding an author
        if (createMode && ui->tableWidgetAuthors->currentIndex().row() == (ui->tableWidgetAuthors->rowCount() - 1)) {
            createMode = false;
        }

        ui->lineEditFirstName->clear();
        ui->lineEditLastName->clear();

    } catch(const char* errormsg) {
        qDebug() << errormsg;
    }
}
