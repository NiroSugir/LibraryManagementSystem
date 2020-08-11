#include "applicationwindow.h"
#include "ui_applicationwindow.h"
#include "router.h"

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

void ApplicationWindow::on_actionLogin_triggered()
{
    Router::getInstance()->switchToLoginView();
}

void ApplicationWindow::on_actionFind_Books_triggered()
{
    Router::getInstance()->switchToBookView();
}

void ApplicationWindow::on_actionSign_up_triggered()
{
    Router::getInstance()->switchToSignupView();
}
