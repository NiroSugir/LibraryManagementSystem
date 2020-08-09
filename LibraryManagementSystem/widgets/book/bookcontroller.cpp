#include "bookcontroller.h"

BookController::BookController(ApplicationWindow *_mainWindow):
    applicationWindow{_mainWindow}, view{new BookView}, model{new BookModel}
{
    vector<string> *categories = new vector<string>{"Biography", "Science-Fiction", "Mystery", "Fantasy"};
    view->initialize(categories);

    applicationWindow->setMainView(view);
}
