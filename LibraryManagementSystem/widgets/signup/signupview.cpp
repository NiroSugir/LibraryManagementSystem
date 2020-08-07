#include "signupview.h"
#include "ui_signupview.h"

SignupView::SignupView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupView)
{
    ui->setupUi(this);
}

SignupView::~SignupView()
{
    delete ui;
}
