#include "application.h"
#include "ui_application.h"
#include "widgets/book/bookview.h"

Application::Application(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Application)
{
    ui->setupUi(this);

    // TODO: Retrieve the app name from constants and append the current "route" to the title name"
    this->setWindowTitle("Library Management System");

    ui->stackedWidgetContent->insertWidget(0, new BookView);
}

Application::~Application()
{
    delete ui;
}

