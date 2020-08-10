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

    // TODO: delete all history (eg: clear list of controller references)

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
    // TODO: push to history vector
    BookController *bookController = new BookController{&applicationWindow};
}

void Router::switchToSignupView()
{
    // TODO: push to history vector
    SignupController *signupController = new SignupController{&applicationWindow};
}

void Router::switchToLoginView()
{
    LoginController *loginController = new LoginController{&applicationWindow};
}

Router::Session::Session(User _user)
{
    loggedInUser = &_user;
}
