#include "purchasebookcontroller.h"

#include "widgets/author/authormodel.h"
#include "widgets/book/bookmodel.h"


PurchaseBookController::PurchaseBookController(const User *_currentUser)
{
     currentUser = _currentUser;
}

PurchaseBookController::~PurchaseBookController()
{
    // NB: let the framework handle deleting the view. the parent (window will handle deleting the child UIs)
    applicationWindow = nullptr;
    if (model) delete model;
    model = nullptr;
}

void PurchaseBookController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new PurchaseBookView;
    model = new PurchaseBookModel{currentUser};

    applicationWindow->setMainView(view);
    applicationWindow->setTitle("Purchase Books");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();

    view->initialize(currentUser, (AuthorModel{}).getAllDistinctAuthorsFromDb(), (BookModel{currentUser}).getCategories());
    this->view->populateBooksOnSale(this->model->getBooksListedForSale());
}

void PurchaseBookController::bindEventHandlersToView()
{
    function<void (SellableBook)> handlePurchaseBook = [this](SellableBook book) {
        this->model->purchaseBook(book);
        this->view->populateBooksOnSale(this->model->getBooksListedForSale());
        this->view->clearListing();
    };

    this->view->setEventHandlers(handlePurchaseBook);
}
