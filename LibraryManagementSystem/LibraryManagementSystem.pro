QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    applicationwindow.cpp \
    dbconnection.cpp \
    main.cpp \
    models/author.cpp \
    models/book.cpp \
    models/sellablebook.cpp \
    models/user.cpp \
    router.cpp \
    widgets/_helper/controller.cpp \
    widgets/author/authorcontroller.cpp \
    widgets/author/authormodel.cpp \
    widgets/author/authorview.cpp \
    widgets/book/bookcontroller.cpp \
    widgets/book/bookmodel.cpp \
    widgets/book/bookview.cpp \
    widgets/login/logincontroller.cpp \
    widgets/login/loginmodel.cpp \
    widgets/login/loginview.cpp \
    widgets/main/mainview.cpp \
    widgets/purchaseBook/purchasebookcontroller.cpp \
    widgets/purchaseBook/purchasebookmodel.cpp \
    widgets/purchaseBook/purchasebookview.cpp \
    widgets/signup/signupcontroller.cpp \
    widgets/signup/signupmodel.cpp \
    widgets/signup/signupview.cpp \
    widgets/supplierHome/supplierhomecontroller.cpp \
    widgets/supplierHome/supplierhomemodel.cpp \
    widgets/supplierHome/supplierhomeview.cpp \
    widgets/userManagement/usermanagementcontroller.cpp \
    widgets/userManagement/usermanagementmodel.cpp \
    widgets/userManagement/usermanagementview.cpp

HEADERS += \
    applicationwindow.h \
    dbconnection.h \
    models/RoleString.h \
    models/author.h \
    models/book.h \
    models/role.h \
    models/sellablebook.h \
    models/user.h \
    router.h \
    widgets/_helper/controller.h \
    widgets/author/authorcontroller.h \
    widgets/author/authormodel.h \
    widgets/author/authorview.h \
    widgets/book/bookcontroller.h \
    widgets/book/bookmodel.h \
    widgets/book/bookview.h \
    widgets/login/logincontroller.h \
    widgets/login/loginmodel.h \
    widgets/login/loginview.h \
    widgets/main/mainview.h \
    widgets/purchaseBook/purchasebookcontroller.h \
    widgets/purchaseBook/purchasebookmodel.h \
    widgets/purchaseBook/purchasebookview.h \
    widgets/signup/signupcontroller.h \
    widgets/signup/signupmodel.h \
    widgets/signup/signupview.h \
    widgets/supplierHome/supplierhomecontroller.h \
    widgets/supplierHome/supplierhomemodel.h \
    widgets/supplierHome/supplierhomeview.h \
    widgets/userManagement/usermanagementcontroller.h \
    widgets/userManagement/usermanagementmodel.h \
    widgets/userManagement/usermanagementview.h

FORMS += \
    applicationwindow.ui \
    widgets/author/authorview.ui \
    widgets/book/bookview.ui \
    widgets/login/loginview.ui \
    widgets/main/mainview.ui \
    widgets/purchaseBook/purchasebookview.ui \
    widgets/signup/signupview.ui \
    widgets/supplierHome/supplierhomeview.ui \
    widgets/userManagement/usermanagementview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
