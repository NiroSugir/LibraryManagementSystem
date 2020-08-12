#ifndef ROUTER_H
#define ROUTER_H

#include "applicationwindow.h"
#include "widgets/_helper/controller.h"
#include "widgets/book/bookcontroller.h"
#include "widgets/signup/signupcontroller.h"
#include "widgets/login/logincontroller.h"
#include "widgets/author/authorcontroller.h"
#include "widgets/userManagement/usermanagementcontroller.h"
#include <vector>
#include <QObject>
#include "models/user.h"

using std::vector;

class Router: public QObject {

private:
    class Session {
        private:
            User* loggedInUser{nullptr};

        public:
            Session(User _user);

            const User &getUser();
    };

    // Note: no point deleting a pointer for a singleton variable. it's
    // practically a global and exists for the duration of the app.
    // It gets deleted from the heap when app closes.
    static Router *instance;

    ApplicationWindow applicationWindow;
    Session *currentSession{nullptr};
    vector<Controller *> history{};
    signed int historyIndex{-1};

    // Private constructor so that no objects can be created.
    Router();

    void clearSession();

    // MAY ONLY BE INVOKED BY LOGINCONTROLLER AFTER AUTHENTICATING USER
    void loginUser(User _user);

    void updateViewAfterChangingRoutes(Controller *_controller);
    void updateHistoryButtons();

    void setRoutesAuthenticated(bool isAuthenticated);
    void enableDisableAccessibleRoutes(Role role);

public:
    // only login controller may use private loginUser method
    friend class LoginController;

    static Router *getInstance();

    // uncloneable
    Router(Router& other) = delete;

    // unassignable
    void operator=(const Router&) = delete;

    void logout();

    void switchToAuthorView();

    void switchToBookView();

    void switchToSignupView();

    void switchToLoginView();

    void switchToUserManagementView();

    bool canGoBack();

    bool canGoForward();

    void goBack();

    void goForward();

    void handleProfileClick();

};

#endif // ROUTER_H
