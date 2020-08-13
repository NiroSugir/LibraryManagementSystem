#include "bookcontroller.h"
#include "models/borrowablebook.h"
//#include "router.h"

void BookController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new BookView;
    model = new BookModel{currentUser};

    applicationWindow->setMainView(view);
    applicationWindow->setTitle("Books");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();

    view->initialize(currentUser);
}

BookController::~BookController()
{
    // NB: let the framework handle deleting the view. the parent (window will handle deleting the child UIs)
    applicationWindow = nullptr;
    if (model) delete model;
    model = nullptr;
}

void BookController::bindEventHandlersToView()
{
    function<void (string)> handleSearch = [this](string searchString) {
        try {
            vector<BorrowableBook> books{this->model->keywordSearch(searchString)};

            this->view->updateSearchResults(books);
        } catch (const char* errorMsg) {
            throw errorMsg;
        }
    };

    function<void (int)> handleChangeSelectedBook = [this](int selectedIndex) {
        BorrowableBook book{this->model->getBook(selectedIndex)};
        this->view->viewSelectedBook(book);
    };

    function<void ()> handleRetrieveCategories = [this]() {
        vector<string> categories{this->model->getCategories()};
        this->view->populateCategories(categories);
    };

    this->view->setEventHandlers(handleSearch, handleChangeSelectedBook, handleRetrieveCategories);
}

BookController::BookController(const User *_currentUser)
{
    currentUser = _currentUser;
}
