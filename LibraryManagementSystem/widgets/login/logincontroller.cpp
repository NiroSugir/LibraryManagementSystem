#include "logincontroller.h"
#include "router.h"

void LoginController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new LoginView;
    model = new LoginModel;

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
        Router * r = Router::getInstance();
        r->loginUser(user);
    };

    view->setEventHandlers(handleLogin);
}

LoginController::~LoginController()
{
    // NB: let the framework handle deleting the view. the parent (window will handle deleting the child UIs)
    applicationWindow = nullptr;
    if (model) delete model;
    model = nullptr;
}
