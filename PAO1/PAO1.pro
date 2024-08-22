QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartBox.cpp \
    chartaria.cpp \
    charttemp.cpp \
    chartvent.cpp \
    collezione.cpp \
    editDialog.cpp \
    main.cpp \
    mainwindow.cpp \
    sensorBox.cpp \
    sensorearia.cpp \
    sensorefumo.cpp \
    sensoretemp.cpp \
    sensorevent.cpp \
    sensori.cpp \
    visitor.cpp

HEADERS += \
    chartBox.h \
    chartaria.h \
    charttemp.h \
    chartvent.h \
    collezione.h \
    editDialog.h \
    mainwindow.h \
    sensorBox.h \
    sensorearia.h \
    sensorefumo.h \
    sensoretemp.h \
    sensorevent.h \
    sensori.h \
    visitor.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
