#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <QMessageBox>

using std::function;
using std::string;

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

    void setEventHandlers(
        function<void (string, string)> _handleLogin
    );

private slots:
    void on_buttonReset_clicked();
    void on_buttonLogin_clicked();
    void on_lineEditUsername_textChanged(const QString &arg1);
    void on_lineEditPassword_textChanged(const QString &arg1);

private:
    Ui::LoginView *ui;

    void enableLoginButtonIfPossiblyValidCredentials();
    void login();

    function<void (string, string)> handleLogin;

};

#endif // LOGINVIEW_H
