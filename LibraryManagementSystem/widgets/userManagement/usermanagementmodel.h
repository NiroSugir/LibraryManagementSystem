#ifndef USERMANAGEMENTMODEL_H
#define USERMANAGEMENTMODEL_H

#include <vector>
#include "dbconnection.h"
#include "models/user.h"
#include "models/role.h"

using std::vector;
using std::to_string;

enum ValidationStatus { Any, Validated, Unvalidated };

class UserManagementModel
{
public:
    ~UserManagementModel();
    vector<User> loadUsers(ValidationStatus _validationStatus = ValidationStatus::Any);
    User changeSelectedUser(int selectedIndex);

private:
    ValidationStatus validationStatus;
    vector<User> users{};
    User *selectedUser{nullptr};
};

#endif // USERMANAGEMENTMODEL_H
