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
    ApplicationWindow *applicationWindow{nullptr};
    SignupView *view{nullptr};
    SignupModel *model{nullptr};

protected:
    void bindEventHandlersToView() override;

public:
    void init(ApplicationWindow *_mainWindow) override;
};

#endif // SIGNUPCONTROLLER_H
