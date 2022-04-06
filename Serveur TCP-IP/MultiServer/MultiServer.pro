#-------------------------------------------------
#
# Project created by QtCreator 2022-04-05T10:52:41
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = MultiServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    mytread.cpp

HEADERS += \
    myserver.h \
    mytread.h
