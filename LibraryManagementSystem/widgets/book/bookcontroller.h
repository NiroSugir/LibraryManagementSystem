#ifndef BOOKCONTROLLER_H
#define BOOKCONTROLLER_H

#include "bookview.h"
#include "bookmodel.h"
#include "applicationwindow.h"
#include <QObject>

class BookController
{
private:
    ApplicationWindow *applicationWindow;
    BookView *view;
    BookModel *model;

    void bindEventHandlersToView();

public:
    BookController(ApplicationWindow *_mainWindow);
};

#endif // BOOKCONTROLLER_H
