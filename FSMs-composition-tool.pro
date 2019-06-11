#-------------------------------------------------
#
# Project created by QtCreator 2019-01-27T22:38:37
#
#-------------------------------------------------

QT       += core gui xmlpatterns testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FSMs-composition-tool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    fsm-item.cpp \
    link-item.cpp \
    arrow-item.cpp \
    composition-item.cpp \
    common-item.cpp \
    view.cpp \
    fsm.cpp \
    link.cpp \
    composition.cpp \
    scene.cpp

HEADERS += \
        mainwindow.h \
    fsm-item.h \
    link-item.h \
    arrow-item.h \
    globals.h \
    composition-item.h \
    common-item.h \
    view.h \
    fsm.h \
    link.h \
    composition.h \
    scene.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    schemas.qrc
