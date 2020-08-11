#include "loginview.h"
#include "ui_loginview.h"

#include "models/user.h"

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);

    enableLoginButtonIfPossiblyValidCredentials();
    ui->lineEditUsername->setFocus();
}

LoginView::~LoginView()
{
    if (ui) delete ui;
}

void LoginView::setEventHandlers(function<void (string, string)> _handleLogin)
{
    handleLogin = _handleLogin;
}

void LoginView::on_buttonReset_clicked()
{
    ui->lineEditUsername->setText("");
    ui->lineEditPassword->setText("");

    ui->lineEditUsername->setFocus();
}

void LoginView::on_buttonLogin_clicked()
{
    try {
        handleLogin(ui->lineEditUsername->text().toStdString(),ui->lineEditPassword->text().toStdString());
    } catch (const char* errorMsg) {
        // show an alert box with the error message
        QMessageBox alert;
        alert.setWindowTitle("Login Error!");
        alert.setText(errorMsg);
        alert.setIcon(QMessageBox::Critical);
        alert.setStandardButtons(QMessageBox::Ok);
        alert.setDefaultButton(QMessageBox::Ok);

        alert.exec();
    }
}

void LoginView::on_lineEditUsername_textChanged(const QString &_)
{
    // check after any text has changed if login button should be enable
    enableLoginButtonIfPossiblyValidCredentials();
}

void LoginView::on_lineEditPassword_textChanged(const QString &_)
{
    // check after any text has changed if login button should be enable
    enableLoginButtonIfPossiblyValidCredentials();
}

void LoginView::enableLoginButtonIfPossiblyValidCredentials()
{
    // enable login button only if username & password meat the validation criteria.
    // This is to prevent querying a possibly busy database in production

    bool valid{true};

    try {
        User::usernameIsValid(ui->lineEditUsername->text().toStdString());
        User::passwordIsValid(ui->lineEditPassword->text().toStdString());
    } catch (const char* msg) {
        valid = false;
    }

    ui->buttonLogin->setDisabled(!(valid));
}

