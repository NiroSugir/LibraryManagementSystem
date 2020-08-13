#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include "widgets/main/mainview.h"

#include <QMainWindow>

using std::string;

namespace Ui {
class ApplicationWindow;
}

class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

    void setMainView(QWidget *_widget);
    void setFooterView(QWidget *_widget);
    void setNavigationView(QWidget *_widget);
    void setTitle(std::string _title);
    void setStatusbarMessage(std::string _statusbarMessage);

    void setBackButtonStatus(bool enabled);
    void setForwardButtonStatus(bool enabled);
    void setProfileNameOnLabel(string profileName);
    void setSignupButtonStatus(bool enabled);
    void setLoginButtonStatus(bool enabled);
    void setLogoutButtonStatus(bool enabled);
    void setAuthorRouteButtonVisibility(bool visible);
    void setMemberManagementRouteButtonVisibility(bool visible);
    void setListBooksForSaleButtonVisibility(bool visible);

private slots:
    void on_actionLogin_triggered();

    void on_actionFind_Books_triggered();

    void on_actionSign_up_triggered();

    void on_actionBack_triggered();

    void on_actionForward_triggered();

    void on_actionLogout_triggered();

    void on_actionLabelUsername_triggered();

    void on_actionAuthor_triggered();

    void on_actionManage_Members_triggered();

    void on_actionList_Books_For_Sale_triggered();

    void on_actionPurchase_Books_triggered();

private:
    Ui::ApplicationWindow *ui;
//    Ui::MainView *mainView;
    MainView *mainView;

};

#endif // APPLICATIONWINDOW_H
