#ifndef SIGNUPCONTROLLER_H
#define SIGNUPCONTROLLER_H

#include "signupview.h"
#include "signupmodel.h"
#include "applicationwindow.h"
#include <QObject>
#include "models/role.h"
#include "widgets/_helper/controller.h"

using std::function;
using std::string;

class SignupController: public Controller
{
private:
    ApplicationWindow *applicationWindow;
    SignupView *view;
    SignupModel *model;

protected:
    void bindEventHandlersToView();

public:
    SignupController(ApplicationWindow *_mainWindow);
};

#endif // SIGNUPCONTROLLER_H
