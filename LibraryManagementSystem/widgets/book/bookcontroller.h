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
    ApplicationWindow *applicationWindow;
    BookView *view;
    BookModel *model;

protected:
    void bindEventHandlersToView();

public:
    BookController(ApplicationWindow *_mainWindow);
};

#endif // BOOKCONTROLLER_H
