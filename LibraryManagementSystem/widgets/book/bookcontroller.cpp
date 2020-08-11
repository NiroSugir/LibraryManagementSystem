#include "bookcontroller.h"
#include "models/book.h"

void BookController::init(ApplicationWindow *_mainWindow)
{
    applicationWindow = _mainWindow;
    view = new BookView;
    model = new BookModel;

    vector<string> categories = vector<string>{"Biography", "Science-Fiction", "Mystery", "Fantasy"};
    view->initialize(categories);

    applicationWindow->setMainView(view);
    applicationWindow->setTitle("Books");

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

BookController::~BookController()
{
    applicationWindow = nullptr;
    delete view;
    delete model;
    view = nullptr;
    model = nullptr;
}

void BookController::bindEventHandlersToView()
{
    function<void (string)> handleSearch = [this](string searchString) {
        vector<Book> books{this->model->keywordSearch(searchString)};
        this->view->updateSearchResults(books);
    };

    function<void (int)> handleChangeSelectedBook = [this](int selectedIndex) {
        Book book{this->model->getBook(selectedIndex)};
        this->view->viewSelectedBook(book);
    };

    this->view->setEventHandlers(handleSearch, handleChangeSelectedBook);
}
