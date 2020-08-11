#include "router.h"

Router *Router::instance = 0;

Router::Router()
{

    // Go to default route then show application. This prevents screen flashing on
    // slower computers.
    switchToBookView();
    applicationWindow.show();
}

void Router::loginUser(User _user)
{
    // remove the contents on the hep if there was a session already
    if (currentSession) {
        delete currentSession;
    }

    currentSession = new Router::Session{_user};

    // delete all history (eg: clear list of controller references)
    for(const auto &controller : history) {
        delete controller;
    }

    history.clear();

    // TODO: create routes for this role

    // go to home route for this role
    switchToBookView();
}

void Router::updateViewAfterChangingRoutes(Controller *_controller)
{
    history.push_back(_controller);
    historyIndex++;

    // update toolbar back/forward button accessibility
    applicationWindow.setBackButtonStatus(canGoBack());
    applicationWindow.setForwardButtonStatus(canGoForward());
}

Router *Router::getInstance()
{
    if (!instance) {
        instance = new Router;
    }

    return instance;
}

void Router::switchToBookView()
{
    BookController *bookController = new BookController{&applicationWindow};
    updateViewAfterChangingRoutes(bookController);
}

void Router::switchToSignupView()
{
    SignupController *signupController = new SignupController{&applicationWindow};
    updateViewAfterChangingRoutes(signupController);
}

void Router::switchToLoginView()
{
    LoginController *loginController = new LoginController{&applicationWindow};
    updateViewAfterChangingRoutes(loginController);
}

bool Router::canGoBack()
{
    return historyIndex > 0;
}

bool Router::canGoForward()
{
    return historyIndex > history.size();
}

Router::Session::Session(User _user)
{
    loggedInUser = &_user;
}
