#include "applicationwindow.h"
#include "widgets/book/bookview.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    ApplicationWindow w;
    w.show();

    return a.exec();
}
