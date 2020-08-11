#include "logincontroller.h"
#include "router.h"

LoginController::LoginController(ApplicationWindow *_mainWindow):
    applicationWindow{_mainWindow}, view{new LoginView}, model{new LoginModel}
{
    applicationWindow->setMainView(view);
    applicationWindow->setTitle("Login");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

void LoginController::bindEventHandlersToView()
{
    function<void (string, string)> handleLogin = [this](string username, string password) {
        User user{model->login(username, password)};

        // sets the new session and routes the user to their home route
        Router::getInstance()->loginUser(user);
    };

    view->setEventHandlers(handleLogin);
}
