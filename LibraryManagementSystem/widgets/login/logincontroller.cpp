#include "logincontroller.h"

LoginController::LoginController(ApplicationWindow *_mainWindow):
    applicationWindow{_mainWindow}, view{new LoginView}, model{new LoginModel}
{
    applicationWindow->setMainView(view);

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

void LoginController::bindEventHandlersToView()
{
//    function<void (string)> handleSearch = [this](string searchString) {
//        vector<Book> books{this->model->keywordSearch(searchString)};
//        this->view->updateSearchResults(books);
//    };
}
