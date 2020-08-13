#ifndef SUPPLIERHOMECONTROLLER_H
#define SUPPLIERHOMECONTROLLER_H

#include "supplierhomeview.h"
#include "supplierhomemodel.h"
#include "applicationwindow.h"
#include <QObject>
#include "widgets/_helper/controller.h"

using std::function;
using std::string;

class SupplierHomeController: public Controller
{
private:
    ApplicationWindow *applicationWindow{nullptr};
    SupplierHomeView *view{nullptr};
    SupplierHomeModel *model{nullptr};

    const User *currentUser{nullptr};

protected:
    void bindEventHandlersToView() override;

public:
    SupplierHomeController(const User *_currentUser);
    ~SupplierHomeController();

    void init(ApplicationWindow *_mainWindow) override;
};

#endif // SUPPLIERHOMECONTROLLER_H
