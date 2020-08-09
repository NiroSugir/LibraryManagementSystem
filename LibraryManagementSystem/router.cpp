#include "router.h"

Router *Router::instance = 0;

Router::Router()
{
    // Go to default route then show application. This prevents screen flashing on
    // slower computers.
//    switchToBookView();
    switchToSignUpView();
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

void Router::switchToSignUpView()
{
    // TODO: push to history vector
    SignupController *signUpController = new SignupController{&applicationWindow};
}
