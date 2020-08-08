#include "applicationwindow.h"
#include "ui_applicationwindow.h"

ApplicationWindow::ApplicationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationWindow),
//    mainView(new Ui::MainView)
    mainView(new MainView)
{
    ui->setupUi(this);
    setCentralWidget(mainView);
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
    delete mainView;
}

void ApplicationWindow::setMainView(QWidget *widget)
{
    mainView->setContent(widget);
}
