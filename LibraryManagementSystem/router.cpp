#include "router.h"
#include <QDebug>

Router *Router::instance = 0;

Router::Router()
{
    // Go to default route then show application. This prevents screen flashing on
    // slower computers.
//    switchToBookView();
    switchToPurchaseBooks();


    setRoutesAuthenticated(false);
    enableDisableAccessibleRoutes(false, Role::Guest);

    applicationWindow.setProfileNameOnLabel("You are browsing as a Guest. Sign up for free!");

    applicationWindow.show();
}

void Router::clearSession()
{
    // remove the contents on the hep if there was a session already
    if (currentSession) {
        delete currentSession;
        currentSession = nullptr;
    }

    // delete all history (eg: clear list of controller references)
    for(auto &controller : history) {
        if (controller) {
            delete controller;
            controller = nullptr;
        };
    }

    // reset history. index will be incremented to the 0th index
    // when the first route is set to it
    history.clear();
    historyIndex = -1;

    setRoutesAuthenticated(false);
    enableDisableAccessibleRoutes(false, Role::Guest);
}

void Router::loginUser(User _user)
{
    clearSession();

    currentSession = new Router::Session{_user};

    applicationWindow.setProfileNameOnLabel("Greetings " + _user.getFirstName() + "!");

    // create routes for this role. everything's that's accessible, is so
    // through the toolbars (which are reset when user changes)
    setRoutesAuthenticated(true);
    enableDisableAccessibleRoutes(_user.isValidated(), _user.getRole());

    // go to home route for this role
    switchToBookView();
}

void Router::logout()
{
    clearSession();

    applicationWindow.setProfileNameOnLabel("You are browsing as a Guest. Sign up for free!");

    switchToLoginView();
}

void Router::switchToAuthorView()
{
    AuthorController *authorController = new AuthorController;
    updateViewAfterChangingRoutes(authorController);
}

void Router::updateViewAfterChangingRoutes(Controller *_controller)
{
    _controller->init(&applicationWindow);

    // add to the end of history, if the user's hasn't pressed back. if
    // they passed back, remove all screens forward from this and push at the end of htat
    if (historyIndex < ((signed int) history.size() - 1)) {
        for (int i = historyIndex+1; i < (signed int) history.size(); i++) {
            delete history[i];
            history[i] = nullptr;
        }

        history.resize(historyIndex + 1);
    }
    history.push_back(_controller);
    historyIndex++;

    updateHistoryButtons();
}

void Router::updateHistoryButtons()
{
    // update toolbar back/forward button accessibility
    applicationWindow.setBackButtonStatus(canGoBack());
    applicationWindow.setForwardButtonStatus(canGoForward());
}

void Router::setRoutesAuthenticated(bool isAuthenticated)
{
    applicationWindow.setLoginButtonStatus(!isAuthenticated);
    applicationWindow.setSignupButtonStatus(!isAuthenticated);
    applicationWindow.setLogoutButtonStatus(isAuthenticated);
}

void Router::enableDisableAccessibleRoutes(bool validated, Role role)
{
    applicationWindow.setAuthorRouteButtonVisibility(validated && (role == Role::Staff || role == Role::Supplier));
    applicationWindow.setMemberManagementRouteButtonVisibility(validated && role == Role::Staff);
    applicationWindow.setListBooksForSaleButtonVisibility(validated && role == Role::Supplier);
}

Router *Router::getInstance()
{
    if (!instance) {
        instance = new Router;
    }

    return instance;
}

const User *Router::getLoggedInUser()
{
    if (currentSession) {
        return currentSession->getUser();
    }

    return nullptr;
}

void Router::switchToBookView()
{
    BookController *bookController = new BookController{getLoggedInUser()};
    updateViewAfterChangingRoutes(bookController);
}

void Router::switchToSignupView()
{
    SignupController *signupController = new SignupController;
    updateViewAfterChangingRoutes(signupController);
}

void Router::switchToLoginView()
{
    LoginController *loginController = new LoginController;
    updateViewAfterChangingRoutes(loginController);
}

void Router::switchToUserManagementView()
{
    UserManagementController *userManagementController = new UserManagementController;
    updateViewAfterChangingRoutes(userManagementController);
}

void Router::switchToListBooksForSaleView()
{
    SupplierHomeController *supplierHomeController = new SupplierHomeController{getLoggedInUser()};
    updateViewAfterChangingRoutes(supplierHomeController);
}

void Router::switchToPurchaseBooks()
{
    PurchaseBookController *purchaseHomeController = new PurchaseBookController{getLoggedInUser()};
    updateViewAfterChangingRoutes(purchaseHomeController);
}

bool Router::canGoBack()
{
    return historyIndex > 0;
}

bool Router::canGoForward()
{
    return historyIndex < ((signed int) history.size() - 1);
}

void Router::goBack()
{
    history[--historyIndex]->init(&applicationWindow);
    updateHistoryButtons();

}

void Router::goForward()
{
    history[++historyIndex]->init(&applicationWindow);

    updateHistoryButtons();
}

void Router::handleProfileClick()
{
    if (currentSession){
         User u{*currentSession->getUser()};

         // TODO: route to user's profile
    } else {
        switchToSignupView();
    }
}

Router::Session::Session(User _user)
{
    loggedInUser = new User{_user};
}

Router::Session::~Session()
{
    if (loggedInUser) {
        delete loggedInUser;
        loggedInUser = nullptr;
    }
}

const User *Router::Session::getUser()
{
    return loggedInUser;
}
