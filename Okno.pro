QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    kod.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Interval.h \
    kod.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

QMAKE_CXX = g++
QMAKE_CC = gcc
QMAKE_LINK = g++
QMAKE_LINK_SHLIB = g++

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
LIBS += -lboost_system -lboost_filesystem -lboost_program_options -lmpfr


DISTFILES += \
    IntervalArithmetic.pas \
    IntervalArithmetic32and64.pas \
    Okno.pro.user
