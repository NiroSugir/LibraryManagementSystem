#ifndef SIGNUPCONTROLLER_H
#define SIGNUPCONTROLLER_H

#include "signupview.h"
#include "signupmodel.h"
#include "applicationwindow.h"
#include <QObject>
#include "models/Role.h"

using std::function;
using std::string;

class SignupController
{
private:
    ApplicationWindow *applicationWindow;
    SignupView *view;
    SignupModel *model;

    void bindEventHandlersToView();

public:
    SignupController(ApplicationWindow *_mainWindow);
};

#endif // SIGNUPCONTROLLER_H
