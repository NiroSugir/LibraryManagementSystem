//#include "applicationwindow.h"
#include "router.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    // create the router instance, which creates and maintains the application window
    Router::getInstance();

    return a.exec();
}
