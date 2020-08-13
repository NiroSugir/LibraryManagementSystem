#ifndef PURCHASEBOOKCONTROLLER_H
#define PURCHASEBOOKCONTROLLER_H

#include "purchasebookview.h"
#include "purchasebookmodel.h"
#include "applicationwindow.h"
#include <QObject>
#include "widgets/_helper/controller.h"
#include "models/user.h"

using std::function;
using std::string;

class PurchaseBookController: public Controller
{
private:
    ApplicationWindow *applicationWindow{nullptr};
    PurchaseBookView *view{nullptr};
    PurchaseBookModel *model{nullptr};

    const User *currentUser{nullptr};

protected:
    void bindEventHandlersToView() override;

public:
    PurchaseBookController(const User *_currentUser);
    ~PurchaseBookController();

    void init(ApplicationWindow *_mainWindow) override;
};

#endif // PURCHASEBOOKCONTROLLER_H
