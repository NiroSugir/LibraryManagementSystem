#ifndef BOOKCONTROLLER_H
#define BOOKCONTROLLER_H

#include "bookview.h"
#include "bookmodel.h"
#include "applicationwindow.h"
#include <QObject>
#include "widgets/_helper/controller.h"

using std::function;
using std::string;

class BookController: public Controller
{
private:
    ApplicationWindow *applicationWindow{nullptr};
    BookView *view{nullptr};
    BookModel *model{nullptr};

    const User *currentUser{nullptr};

protected:
    void bindEventHandlersToView() override;

public:
    BookController(const User *_currentUser);
    ~BookController();
    void init(ApplicationWindow *_mainWindow) override;
};

#endif // BOOKCONTROLLER_H
