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
    void setWindowTitle(std::string _title);
    void setStatusbarMessage(std::string _statusbarMessage);

private:
    Ui::ApplicationWindow *ui;
//    Ui::MainView *mainView;
    MainView *mainView;
};

#endif // APPLICATIONWINDOW_H
