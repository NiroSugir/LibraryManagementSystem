#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "ui_mainview.h"

#include <QWidget>

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView();

    void setContent(QWidget *widget);

private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
