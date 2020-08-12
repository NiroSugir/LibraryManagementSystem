#include "authorcontroller.h"

void AuthorController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new AuthorView;
    model = new AuthorModel;

    // populate the authors view with data from db
    this->view->updateAuthorsList(this->model->getAllDistinctAuthorsFromDb());

    applicationWindow->setMainView(view);
    applicationWindow->setTitle("Books");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

void AuthorController::bindEventHandlersToView()
{
//    this->view->setEventHandlers(handleSearch, handleChangeSelectedBook);
}

AuthorController::~AuthorController()
{
    // NB: let the framework handle deleting the view. the parent (window will handle deleting the child UIs)
    applicationWindow = nullptr;
    if (model) delete model;
    model = nullptr;
}
