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

protected:
    void bindEventHandlersToView() override;

public:
    void init(ApplicationWindow *_mainWindow) override;

    ~BookController();
};

#endif // BOOKCONTROLLER_H
