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

void UserManagementView::setEventHandlers(function<void (ValidationStatus)> _handleLoadUsers, function<void (int)> _handleChangeSelectedUser)
{
    handleLoadUsers = _handleLoadUsers;
    handleChangeSelectedUser = _handleChangeSelectedUser;

    handleLoadUsers(ValidationStatus::Any);
}

void UserManagementView::showUsers(vector<User> users)
{
    ui->tableWidgetRegisteredUsers->clearContents();
    ui->tableWidgetRegisteredUsers->setRowCount(users.size());

    int row = 0;
    for (User const &user: users) {
        QString username{QString::fromStdString(user.getUsername())};
        QString role{QString::fromStdString(RoleString[user.getRole()])};
        QString validated{user.getValidated() ? "Yes": "No"};

        ui->tableWidgetRegisteredUsers->setItem(row, 0, new QTableWidgetItem{username});
        ui->tableWidgetRegisteredUsers->setItem(row, 1, new QTableWidgetItem{role});
        ui->tableWidgetRegisteredUsers->setItem(row, 2, new QTableWidgetItem{validated});

        row++;
    }
}

void UserManagementView::viewSelectedUser(User user)
{
    if (!ui->groupBoxUserInfo->isEnabled()) {
        ui->groupBoxUserInfo->setEnabled(true);
    }
    ui->labelFirstName->setText(user.getFirstName().c_str());
    ui->labelLastName->setText(user.getLastName().c_str());
    ui->labelUsername->setText(user.getUsername().c_str());
    ui->labelValidated->setText(user.getValidated() ? "Yes" : "No");
    ui->labelRole->setText(RoleString[user.getRole()].c_str());
    ui->pushButtonApprove->setEnabled(!user.getValidated());

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

void UserManagementView::on_tableWidgetRegisteredUsers_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    // user changes only if the row changes
    if (currentRow != previousRow && currentRow > -1) {
        // handle change user
        handleChangeSelectedUser(currentRow);
    }
}
