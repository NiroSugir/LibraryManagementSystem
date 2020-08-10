#include "router.h"

Router *Router::instance = 0;

Router::Router()
{
    // Go to default route then show application. This prevents screen flashing on
    // slower computers.
//    switchToBookView();
    switchToLoginView();
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

    // create routes for this role



    // go to home route for this role
    switchToBookView();
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
    history.push_back(bookController);
}

void Router::switchToSignupView()
{
    SignupController *signupController = new SignupController{&applicationWindow};
    history.push_back(signupController);
}

void Router::switchToLoginView()
{
    LoginController *loginController = new LoginController{&applicationWindow};
    history.push_back(loginController);
}

Router::Session::Session(User _user)
{
    loggedInUser = &_user;
}
