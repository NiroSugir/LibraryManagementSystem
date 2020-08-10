#ifndef CONTROLLER_H
#define CONTROLLER_H

// Controller Interface
class Controller
{
protected:
    virtual void bindEventHandlersToView() = 0;

public:
    virtual ~Controller();
};

#endif // CONTROLLER_H
