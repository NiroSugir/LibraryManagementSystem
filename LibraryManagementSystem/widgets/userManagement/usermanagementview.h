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
        function<void (ValidationStatus)> _handleLoadUsers
    );
    void showUsers(vector<User> users);

private:
    Ui::UserManagementView *ui;

    void setupSearchResultsTable();

    function<void (ValidationStatus)> handleLoadUsers;
};

#endif // USERMANAGEMENTVIEW_H
