#ifndef SIGNUPVIEW_H
#define SIGNUPVIEW_H

#include <QWidget>
#include <QMessageBox>

using std::string;
using std::function;

namespace Ui {
class SignupView;
}

class SignupView : public QWidget
{
    Q_OBJECT

public:
    explicit SignupView(QWidget *parent = nullptr);
    ~SignupView();

    void redirectToLoginScreen();
    void setEventHandlers(
        function<void (string, string, string, string, string)> _handleSignup
    );

private slots:
    void on_pushButtonClear_clicked();
    void on_pushButtonSignup_clicked();

private:
    Ui::SignupView *ui;

    function<void (string, string, string, string, string)> handleSignup;
};

#endif // SIGNUPVIEW_H
