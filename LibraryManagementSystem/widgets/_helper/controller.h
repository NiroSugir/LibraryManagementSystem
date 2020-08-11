#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "applicationwindow.h"

// Controller Interface
class Controller
{
protected:
    virtual void bindEventHandlersToView() = 0;

public:
    virtual ~Controller();
    virtual void init(ApplicationWindow *_mainWindow) = 0;
};

#endif // CONTROLLER_H
