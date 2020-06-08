QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShapePainterPlugin
TEMPLATE = lib
DESTDIR = ../output/ShapePainter/plugins

CONFIG += plugin
INCLUDEPATH += $$PWD/../ShapePainter

HEADERS += \
    brushplugin.h

SOURCES += \
    brushplugin.cpp

OTHER_FILES += \
    brushplugin.json
