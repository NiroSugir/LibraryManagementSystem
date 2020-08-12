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
    function<void (int)> handleSelectAuthorForEdit = [this](int selectedIndex) {
        Author author{this->model->selectAuthorAtIndex(selectedIndex)};
        this->view->selectAuthorForEdit(author);
    };

    function<int (void)> handleCreateNewAuthor = [this]() {
        Author author{this->model->createNewAuthor()};
        auto authors{this->model->getAllLocalAuthors()};
        this->view->updateAuthorsList(authors);
        this->view->selectAuthorForEdit(author);

        return authors.size() - 1;
    };

    function<void (string, string)> handleSaveChanges = [this](string firstName, string lastName) {
        this->model->saveChanges(firstName, lastName);
        auto authors{this->model->getAllDistinctAuthorsFromDb()};
        this->view->updateAuthorsList(authors);
    };

    this->view->setEventHandlers(
        handleSelectAuthorForEdit,
        handleCreateNewAuthor,
        handleSaveChanges
    );
}

AuthorController::~AuthorController()
{
    // NB: let the framework handle deleting the view. the parent (window will handle deleting the child UIs)
    applicationWindow = nullptr;
    if (model) delete model;
    model = nullptr;
}
