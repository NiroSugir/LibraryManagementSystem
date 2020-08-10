#include "signupview.h"
#include "ui_signupview.h"

#include "router.h"

SignupView::SignupView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupView)
{
    ui->setupUi(this);


    // temp
    ui->lineEditFirstName->setText("Niro");
    ui->lineEditLastName->setText("Sugir");
    ui->lineEditUsername->setText("niro");
    ui->lineEditPassword->setText("123456789");
    ui->lineEditVerifyPassword->setText("123456789");
    ui->radioButtonMember->setChecked(true);

}

SignupView::~SignupView()
{
    delete ui;
}

void SignupView::redirectToLoginScreen()
{
    Router::getInstance()->switchToBookView();
}

void SignupView::setEventHandlers(function<void (string, string, string, string, string, Role)> _handleSignup)
{
    handleSignup = _handleSignup;
}

void SignupView::on_pushButtonClear_clicked()
{
    ui->lineEditFirstName->setText("");
    ui->lineEditLastName->setText("");
    ui->lineEditUsername->setText("");
    ui->lineEditPassword->setText("");
    ui->lineEditVerifyPassword->setText("");
    ui->radioButtonMember->setChecked(true);

    ui->lineEditFirstName->setFocus();
}

void SignupView::on_pushButtonSignup_clicked()
{
    try {
        // event handler calls redirect if there are no errors
        // validating the form.
        this->handleSignup(
            ui->lineEditFirstName->text().toStdString(),
            ui->lineEditLastName->text().toStdString(),
            ui->lineEditUsername->text().toStdString(),
            ui->lineEditPassword->text().toStdString(),
            ui->lineEditVerifyPassword->text().toStdString(),
            ui->radioButtonMember->isChecked() ? Role::Member :
                ui->radioButtonStaff->isChecked() ? Role::Staff : Role::Supplier
        );
    } catch (const char* msg) {
        // show an alert box with the error message
        QMessageBox alert;
        alert.setWindowTitle("Registration Error!");
        alert.setText(msg);
        alert.setIcon(QMessageBox::Critical);
        alert.setStandardButtons(QMessageBox::Ok);
        alert.setDefaultButton(QMessageBox::Ok);

        alert.exec();
    }

}
