#ifndef ERRORALERT_H
#define ERRORALERT_H

#include <QMessageBox>

using std::string;

class ErrorAlert
{
public:
    ErrorAlert(const char* errorMessage = "Internal DB Error! Could not access database. Please wait a while and try again. If problem persists, reinstall the app or call at 1-800-SHOULD-HAVE-PAID-FOR-SUPPORT ext. HAHA");

private:
    void showAlertBox(const char* errorMessage);
};

#endif // ERRORALERT_H
