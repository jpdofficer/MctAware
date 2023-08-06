QT       += core gui network xml
QT += widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MctVehicleData.cpp \
    RoutersVehiclesDialog.cpp \
    cradlepointrouter.cpp \
    main.cpp \
    mainwindow.cpp \
    mctvehiclecheck.cpp \
    networkinformation.cpp

HEADERS += \
    CradlePointRouters.h \
    MctVehicleData.h \
    RoutersVehiclesDialog.h \
    cradlepointrouter.h \
    mainwindow.h \
    mctvehiclecheck.h \
    networkinformation.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


