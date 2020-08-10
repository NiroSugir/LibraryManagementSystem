#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
protected:
    virtual void bindEventHandlersToView() = 0;

public:
    ~Controller(){};
};

#endif // CONTROLLER_H
