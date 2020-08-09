#include "bookcontroller.h"
#include "models/book.h"

BookController::BookController(ApplicationWindow *_mainWindow):
    applicationWindow{_mainWindow}, view{new BookView}, model{new BookModel}
{
    vector<string> *categories = new vector<string>{"Biography", "Science-Fiction", "Mystery", "Fantasy"};
    view->initialize(categories);

    applicationWindow->setMainView(view);

    // setup callbacks for the view to communicate with the model
    bindEventHandlersToView();
}

void BookController::bindEventHandlersToView()
{
    std::function<void (std::string)> handleSearch = [this](std::string searchString) {
        vector<Book> books{this->model->keywordSearch(searchString)};
        this->view->updateSearchResults(const &books);
    };

    this->view->setEventHandlers(handleSearch);
}
