#include "bookcontroller.h"
#include "models/book.h"

void BookController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new BookView;
    model = new BookModel;


    applicationWindow->setMainView(view);
    applicationWindow->setTitle("Books");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();

//    vector<string> categories = vector<string>{"Biography", "Science Fiction", "Mystery", "Fantasy", "Horror", "History"};
    view->initialize();
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
            vector<Book> books{this->model->keywordSearch(searchString)};

            this->view->updateSearchResults(books);
        } catch (const char* errorMsg) {
            throw errorMsg;
        }
    };

    function<void (int)> handleChangeSelectedBook = [this](int selectedIndex) {
        Book book{this->model->getBook(selectedIndex)};
        this->view->viewSelectedBook(book);
    };

    function<void ()> handleRetrieveCategories = [this]() {
        vector<string> categories{this->model->getCategories()};
        this->view->populateCategories(categories);
    };


    this->view->setEventHandlers(handleSearch, handleChangeSelectedBook, handleRetrieveCategories);
}
