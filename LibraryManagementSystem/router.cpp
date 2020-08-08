#include "router.h"

Router *Router::instance = 0;

Router::Router()
{
    applicationWindow.show();
}

Router *Router::getInstance()
{
    if (!instance) {
        instance = new Router;
    }

    return instance;
}
