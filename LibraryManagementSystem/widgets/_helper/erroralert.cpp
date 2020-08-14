#include "erroralert.h"

ErrorAlert::ErrorAlert(const char *errorMessage)
{
    showAlertBox(errorMessage);
}

void ErrorAlert::showAlertBox(const char *errorMessage)
{
    // show an alert box with the error message
    QMessageBox alert;
    alert.setWindowTitle("Library Management Sytem: Error");
    alert.setText(errorMessage);
    alert.setIcon(QMessageBox::Critical);
    alert.setStandardButtons(QMessageBox::Ok);
    alert.setDefaultButton(QMessageBox::Ok);

    alert.exec();
}
