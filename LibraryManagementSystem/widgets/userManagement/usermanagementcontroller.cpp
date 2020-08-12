#include "usermanagementcontroller.h"

void UserManagementController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new UserManagementView;
    model = new UserManagementModel;


    applicationWindow->setMainView(view);
    applicationWindow->setTitle("User Management");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

UserManagementController::~UserManagementController()
{
    // NB: let the framework handle deleting the view. the parent (window will handle deleting the child UIs)
    applicationWindow = nullptr;
    if (model) delete model;
    model = nullptr;
}

void UserManagementController::bindEventHandlersToView()
{
    function<void (ValidationStatus)> handleLoadUsers = [this](ValidationStatus validationStatus) {
        vector<User> users{this->model->loadUsers(validationStatus)};
        this->view->showUsers(users);
    };

    function<void (int)> handleChangeSelectedUser = [this](int selectedIndex) {
        User user{this->model->changeSelectedUser(selectedIndex)};
        this->view->viewSelectedUser(user);
    };

    this->view->setEventHandlers(handleLoadUsers, handleChangeSelectedUser);
}
