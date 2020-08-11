#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include "widgets/main/mainview.h"

#include <QMainWindow>

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

private slots:
    void on_actionLogin_triggered();

    void on_actionFind_Books_triggered();

    void on_actionSign_up_triggered();

    void on_actionBack_triggered();

    void on_actionForward_triggered();

    void on_actionLogout_triggered();

private:
    Ui::ApplicationWindow *ui;
//    Ui::MainView *mainView;
    MainView *mainView;

};

#endif // APPLICATIONWINDOW_H
