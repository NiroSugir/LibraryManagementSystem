#ifndef BOOKCONTROLLER_H
#define BOOKCONTROLLER_H

#include "bookview.h"
#include "bookmodel.h"
#include "applicationwindow.h"
#include <QObject>

class BookController
{
private:
    BookView *view;
    BookModel *model;
    ApplicationWindow *applicationWindow;

public:
    BookController(ApplicationWindow *_mainWindow);
};

#endif // BOOKCONTROLLER_H
