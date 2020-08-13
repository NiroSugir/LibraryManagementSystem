#include "supplierhomecontroller.h"
#include "models/sellablebook.h"

SupplierHomeController::SupplierHomeController(const User *_currentUser)
{
    currentUser = _currentUser;
}

SupplierHomeController::~SupplierHomeController()
{
    // NB: let the framework handle deleting the view. the parent (window will handle deleting the child UIs)
    applicationWindow = nullptr;
    if (model) delete model;
    model = nullptr;
}

void SupplierHomeController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new SupplierHomeView;
    model = new SupplierHomeModel{currentUser};

    applicationWindow->setMainView(view);
    applicationWindow->setTitle("Supplier Home");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();

//    view->initialize(currentUser);
}

void SupplierHomeController::bindEventHandlersToView()
{
    function<void (SellableBook)> handleListBookForSale = [this](SellableBook book) {
        this->model->sellBook(book);
//        this->view->viewSelectedBook(book);
    };

//    this->view->setEventHandlers(handleSearch, handleChangeSelectedBook, handleRetrieveCategories);
}
