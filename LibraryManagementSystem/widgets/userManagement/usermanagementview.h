#ifndef USERMANAGEMENTVIEW_H
#define USERMANAGEMENTVIEW_H

#include <QWidget>
#include "models/user.h"
#include "usermanagementmodel.h"

namespace Ui {
class UserManagementView;
}

using std::string;
using std::vector;
using std::function;

class UserManagementView : public QWidget
{
    Q_OBJECT

public:
    explicit UserManagementView(QWidget *parent = nullptr);
    ~UserManagementView();

    void setEventHandlers(
        function<void (ValidationStatus)> _handleLoadUsers,
        function<void (int)> _handleChangeSelectedUser,
        function<void (void)> _handleApproveUser
    );
    void showUsers(vector<User> users);
    void viewSelectedUser(User user);

private slots:
    void on_tableWidgetRegisteredUsers_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_radioButtonValidationValidated_clicked();
    void on_radioButtonValidationAny_clicked();
    void on_radioButtonValidationUnvalidated_clicked();

    void on_pushButtonApprove_clicked();

private:
    Ui::UserManagementView *ui;

    void setupSearchResultsTable();
    void unselectCurrentUser();

    function<void (ValidationStatus)> handleLoadUsers;
    function<void (int)> handleChangeSelectedUser;
    function<void (void)> handleApproveUser;
};

#endif // USERMANAGEMENTVIEW_H
