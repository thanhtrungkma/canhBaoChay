#-------------------------------------------------
#
# Project created by QtCreator 2022-03-18T08:16:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dht11
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
    secdialog.cpp \
    thirddialog.cpp

HEADERS += \
        mainwindow.h \
    secdialog.h \
    thirddialog.h

FORMS += \
        mainwindow.ui \
    secdialog.ui \
    thirddialog.ui

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH += $$PWD

CONFIG += unversioned_libname unversioned_soname

unix:!macx: LIBS += -L$$PWD/ -lwiringPi
unix:!macx: LIBS += -L$$PWD/ -lwiringPiDev


INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
