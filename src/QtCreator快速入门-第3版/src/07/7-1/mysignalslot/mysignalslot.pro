#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T22:32:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mysignalslot
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mydialog.cpp

HEADERS  += widget.h \
    mydialog.h

FORMS    += widget.ui \
    mydialog.ui
