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

    // TODO: remove. created to test as proof of concept. should be done by router
    w.setMainView(new BookView);

    return a.exec();
}
