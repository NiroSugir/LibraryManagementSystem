#include "signupcontroller.h"

SignupController::SignupController(ApplicationWindow *_mainWindow):
    applicationWindow{_mainWindow}, view{new SignupView}, model{new SignupModel}
{
    applicationWindow->setMainView(view);

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

void SignupController::bindEventHandlersToView()
{

}
