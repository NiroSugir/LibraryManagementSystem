#include "usermanagementview.h"
#include "ui_usermanagementview.h"

#include "models/RoleString.h"
#include <QDebug>

UserManagementView::UserManagementView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManagementView)
{
    ui->setupUi(this);

    setupSearchResultsTable();
}

UserManagementView::~UserManagementView()
{
    delete ui;
}

void UserManagementView::setEventHandlers(function<void (ValidationStatus)> _handleLoadUsers)
{
    handleLoadUsers = _handleLoadUsers;

    handleLoadUsers(ValidationStatus::Any);
}

void UserManagementView::showUsers(vector<User> users)
{
    ui->tableWidgetRegisteredUsers->clearContents();
    ui->tableWidgetRegisteredUsers->setRowCount(users.size());
    qDebug() << "num users: " << users.size();

    int row = 0;
    for (auto const &user: users) {
        QString username{QString::fromStdString(user.getUsername())};
        QString role{QString::fromStdString(RoleString[user.getRole()])};
        QString validated{user.getValidated() ? "Yes": "No"};

        ui->tableWidgetRegisteredUsers->setItem(row, 0, new QTableWidgetItem{username});
        ui->tableWidgetRegisteredUsers->setItem(row, 1, new QTableWidgetItem{role});
        ui->tableWidgetRegisteredUsers->setItem(row, 2, new QTableWidgetItem{validated});

        row++;
    }
}

void UserManagementView::setupSearchResultsTable()
{
    // force the columns to occupy the whole table width
    ui->tableWidgetRegisteredUsers->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetRegisteredUsers->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidgetRegisteredUsers->setColumnCount(3);
    ui->tableWidgetRegisteredUsers->setRowCount(0);
    ui->tableWidgetRegisteredUsers->setHorizontalHeaderLabels(QStringList{
        QString{"Username"},
        QString{"Role"},
        QString{"Status"}
    });
}
