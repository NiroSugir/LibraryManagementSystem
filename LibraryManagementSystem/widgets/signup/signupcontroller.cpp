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
    function<void (string, string, string, string, string)> handleSignup = [this](
        string firstName,
        string lastName,
        string username,
        string password,
        string verifyPassword
    ) {
        try {
            this->model->signup(firstName, lastName, username, password, verifyPassword);
        } catch (const char* msg) {
            throw msg;
        }

        this->view->redirectToLoginScreen();
    };

    this->view->setEventHandlers(handleSignup);
}
