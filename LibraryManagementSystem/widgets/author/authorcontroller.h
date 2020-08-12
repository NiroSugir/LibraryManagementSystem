#ifndef AUTHORCONTROLLER_H
#define AUTHORCONTROLLER_H

#include "authorview.h"
#include "authormodel.h"
#include "applicationwindow.h"
#include <QObject>
#include "widgets/_helper/controller.h"

using std::function;

class AuthorController: public Controller
{
private:
    ApplicationWindow *applicationWindow{nullptr};
    AuthorView *view{nullptr};
    AuthorModel *model{nullptr};

protected:
    void bindEventHandlersToView() override;

public:
    ~AuthorController();
    void init(ApplicationWindow *_mainWindow) override;
};

#endif // AUTHORCONTROLLER_H
