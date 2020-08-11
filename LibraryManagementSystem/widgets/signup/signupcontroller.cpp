#include "signupcontroller.h"

void SignupController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new SignupView;
    model = new SignupModel;

    applicationWindow->setMainView(view);
    applicationWindow->setTitle("Sign up");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

void SignupController::bindEventHandlersToView()
{
    function<void (string, string, string, string, string, Role)> handleSignup = [this](
        string firstName,
        string lastName,
        string username,
        string password,
        string verifyPassword,
        Role role
    ) {
        try {
            this->model->signup(firstName, lastName, username, password, verifyPassword, role);
        } catch (const char* msg) {
            throw msg;
        }

        this->view->redirectToLoginScreen();
    };

    this->view->setEventHandlers(handleSignup);
}

SignupController::~SignupController()
{
    // NB: let the framework handle deleting the view. the parent (window will handle deleting the child UIs)
    applicationWindow = nullptr;
    if (model) delete model;
    model = nullptr;
}
