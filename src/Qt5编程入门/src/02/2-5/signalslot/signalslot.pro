#-------------------------------------------------
#
# Project created by QtCreator 2014-02-18T11:55:57
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = signalslot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stringdialog.cpp

HEADERS  += mainwindow.h \
    stringdialog.h

FORMS    += mainwindow.ui \
    stringdialog.ui
