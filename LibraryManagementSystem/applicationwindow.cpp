#include "applicationwindow.h"
#include "ui_applicationwindow.h"
#include "router.h"
#include <QDebug>

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

void ApplicationWindow::setTitle(std::string _title)
{
    setWindowTitle(_title.c_str());
}

void ApplicationWindow::setBackButtonStatus(bool enabled)
{
    ui->actionBack->setEnabled(enabled);
}

void ApplicationWindow::setForwardButtonStatus(bool enabled)
{
    ui->actionForward->setEnabled(enabled);
}

void ApplicationWindow::setProfileNameOnLabel(string profileName)
{
    ui->actionLabelUsername->setText(profileName.c_str());
}

void ApplicationWindow::setSignupButtonStatus(bool enabled)
{
    ui->actionSign_up->setVisible(enabled);
}

void ApplicationWindow::setLoginButtonStatus(bool enabled)
{
    ui->actionLogin->setVisible(enabled);
}

void ApplicationWindow::setLogoutButtonStatus(bool enabled)
{
    ui->actionLogout->setVisible(enabled);
}

void ApplicationWindow::on_actionLogin_triggered()
{
    Router::getInstance()->switchToLoginView();
}

void ApplicationWindow::on_actionLogout_triggered()
{
    Router::getInstance()->logout();
}

void ApplicationWindow::on_actionFind_Books_triggered()
{
    Router::getInstance()->switchToBookView();
}

void ApplicationWindow::on_actionSign_up_triggered()
{
    Router::getInstance()->switchToSignupView();
}

void ApplicationWindow::on_actionBack_triggered()
{
    Router::getInstance()->goBack();
}

void ApplicationWindow::on_actionForward_triggered()
{
    Router::getInstance()->goForward();
}

void ApplicationWindow::on_actionLabelUsername_triggered()
{
    Router::getInstance()->handleProfileClick();
}
