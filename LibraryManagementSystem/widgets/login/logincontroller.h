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
    ApplicationWindow *applicationWindow;
    LoginView *view;
    LoginModel *model;

protected:
    void bindEventHandlersToView();

public:
    LoginController(ApplicationWindow *_mainWindow);
};

#endif // LOGINCONTROLLER_H
