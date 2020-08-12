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
        function<void (int)> _handleChangeSelectedUser
    );
    void showUsers(vector<User> users);
    void viewSelectedUser(User user);

private slots:
    void on_tableWidgetRegisteredUsers_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::UserManagementView *ui;

    void setupSearchResultsTable();

    function<void (ValidationStatus)> handleLoadUsers;
    function<void (int)> handleChangeSelectedUser;
};

#endif // USERMANAGEMENTVIEW_H
