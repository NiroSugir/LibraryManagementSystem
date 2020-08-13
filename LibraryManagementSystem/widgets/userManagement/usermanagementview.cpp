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

void UserManagementView::setEventHandlers(function<void (ValidationStatus)> _handleLoadUsers, function<void (int)> _handleChangeSelectedUser, function<void (void)> _handleApproveUser)
{
    handleLoadUsers = _handleLoadUsers;
    handleChangeSelectedUser = _handleChangeSelectedUser;
    handleApproveUser = _handleApproveUser;

    handleLoadUsers(ValidationStatus::Any);
}

void UserManagementView::showUsers(vector<User> users)
{
    unselectCurrentUser();

    ui->tableWidgetRegisteredUsers->clearContents();
    ui->tableWidgetRegisteredUsers->setRowCount(users.size());

    int row = 0;
    for (const User &user: users) {
        QString username{QString::fromStdString(user.getUsername())};
        QString role{QString::fromStdString(RoleString[user.getRole()])};
        QString validated{user.isValidated() ? "Yes": "No"};

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
    ui->labelValidated->setText(user.isValidated() ? "Yes" : "No");
    ui->labelRole->setText(RoleString[user.getRole()].c_str());
    ui->pushButtonApprove->setEnabled(!user.isValidated());

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
        QString{"Approved"}
    });
}

void UserManagementView::unselectCurrentUser()
{
    ui->groupBoxUserInfo->setEnabled(false);

    ui->labelFirstName->clear();
    ui->labelLastName->clear();
    ui->labelUsername->clear();
    ui->labelValidated->clear();
    ui->labelRole->clear();
    ui->pushButtonApprove->setEnabled(false);
}

void UserManagementView::on_tableWidgetRegisteredUsers_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    // user changes only if the row changes
    if (currentRow != previousRow && currentRow > -1) {
        // handle change user
        handleChangeSelectedUser(currentRow);
    }
}

void UserManagementView::on_radioButtonValidationValidated_clicked()
{
    handleLoadUsers(ValidationStatus::Validated);
}

void UserManagementView::on_radioButtonValidationAny_clicked()
{
    handleLoadUsers(ValidationStatus::Any);
}

void UserManagementView::on_radioButtonValidationUnvalidated_clicked()
{
    handleLoadUsers(ValidationStatus::Unvalidated);
}

void UserManagementView::on_pushButtonApprove_clicked()
{
    handleApproveUser();
    // TODO: if error, do not update view

    // don't move the user out of the current view even if the filter
    // doesn't match the user's new status. it's better keep the user
    // in the view than to have the screen flash with the user moving out.
    // also, that user is selected, so they shoudl remain on screen

    QModelIndexList selectedIndexes = ui->tableWidgetRegisteredUsers->selectionModel()->selectedIndexes();
    // only one row can be selected
    auto selectedRow = selectedIndexes[0].row();
    ui->tableWidgetRegisteredUsers->setItem(selectedRow, 2, new QTableWidgetItem{"Recently Validated"});
}
