QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShapePainter
TEMPLATE = app
DESTDIR = ../output/ShapePainter

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    paintwidget.cpp

HEADERS  += mainwindow.h \
    paintwidget.h \
    brushinterface.h

FORMS    += mainwindow.ui
