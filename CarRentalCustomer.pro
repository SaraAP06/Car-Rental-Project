QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LoginWindow.cpp \
    carlistview.cpp \
    customerdashboard.cpp \
    extensionview.cpp \
    main.cpp \
    myextensionsview.cpp \
    myreservationsview.cpp \
    paymentview.cpp \
    reservationview.cpp \
    session.cpp \
    usermanager.cpp

HEADERS += \
    LoginWindow.h \
    carlistview.h \
    customerdashboard.h \
    extensionview.h \
    myextensionsview.h \
    myreservationsview.h \
    paymentview.h \
    reservationview.h \
    session.h \
    usermanager.h

FORMS += \
    LoginWindow.ui \
    carlistview.ui \
    customerdashboard.ui \
    extensionview.ui \
    myextensionsview.ui \
    myreservationsview.ui \
    paymentview.ui \
    reservationview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
