#ifndef ROUTER_H
#define ROUTER_H

#include "applicationwindow.h"

class Router {
private:
    // Note: no point deleting a pointer for a singleton variable. it's
    // practically a global and exists for the duration of the app.
    // It gets deleted from the heap when app closes.
    static Router *instance;

    ApplicationWindow applicationWindow;

    // Private constructor so that no objects can be created.
    Router();

public:
    static Router *getInstance();

    // uncloneable
    Router(Router& other) = delete;

    // unassignable
    void operator=(const Router&) = delete;
};

#endif // ROUTER_H
