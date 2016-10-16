#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T15:30:22
#
#-------------------------------------------------

QT       += core gui widgets

CONFIG += c++11

TARGET = mScreen
TEMPLATE = app


SOURCES += main.cpp\
        msc.cpp

HEADERS  += msc.h

FORMS    += msc.ui

RESOURCES += \
    msc.qrc

win32:RC_FILE = mScreen.rc

LIBS += -luser32
