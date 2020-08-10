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
