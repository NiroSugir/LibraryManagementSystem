#include "logincontroller.h"

LoginController::LoginController(ApplicationWindow *_mainWindow):
    applicationWindow{_mainWindow}, view{new LoginView}, model{new LoginModel}
{
    applicationWindow->setMainView(view);

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

void LoginController::bindEventHandlersToView()
{
    function<void (string, string)> handleLogin = [this](string username, string password) {
        User user{model->login(username, password)};

        // TODO: set logged in session to true and assign user to it
        // session needs to clear previous browse history
        // session needs to set available routes for this user
        // session will determine what the home route is for users of this role and redirect them
        //  to that route
    };

    view->setEventHandlers(handleLogin);
}
