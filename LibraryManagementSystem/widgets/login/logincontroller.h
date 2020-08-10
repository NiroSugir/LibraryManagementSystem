#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "loginview.h"
#include "loginmodel.h"
#include "applicationwindow.h"
#include <QObject>

using std::function;
using std::string;


class LoginController
{
private:
    ApplicationWindow *applicationWindow;
    LoginView *view;
    LoginModel *model;

    void bindEventHandlersToView();

public:
    LoginController(ApplicationWindow *_mainWindow);
};

#endif // LOGINCONTROLLER_H
