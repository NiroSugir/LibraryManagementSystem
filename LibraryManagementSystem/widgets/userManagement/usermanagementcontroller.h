#ifndef USERMANAGEMENTCONTROLLER_H
#define USERMANAGEMENTCONTROLLER_H

#include "usermanagementview.h"
#include "usermanagementmodel.h"
#include "applicationwindow.h"
#include <QObject>
#include "widgets/_helper/controller.h"

using std::function;
using std::string;

class UserManagementController: public Controller
{
private:
    ApplicationWindow *applicationWindow{nullptr};
    UserManagementView *view{nullptr};
    UserManagementModel *model{nullptr};

protected:
    void bindEventHandlersToView() override;

public:
    ~UserManagementController();
    void init(ApplicationWindow *_mainWindow) override;
};

#endif // USERMANAGEMENTCONTROLLER_H
