#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "loginview.h"
#include "loginmodel.h"
#include "applicationwindow.h"
#include <QObject>
#include "widgets/_helper/controller.h"

using std::function;
using std::string;

class LoginController: public Controller
{
private:
    ApplicationWindow *applicationWindow{nullptr};
    LoginView *view{nullptr};
    LoginModel *model{nullptr};

protected:
    void bindEventHandlersToView() override;

public:
    ~LoginController();
    void init(ApplicationWindow *_mainWindow) override;
};

#endif // LOGINCONTROLLER_H
