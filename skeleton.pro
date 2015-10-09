#-------------------------------------------------
#
# Project created by QtCreator 2015-09-30T16:23:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = skeleton
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    core/profiler.cpp \
    core/colorspace.cpp \
    image/imagetile.cpp \
    image/imagelayer.cpp \
    image/image.cpp

HEADERS  += mainwindow.h \
    core/profiler.h \
    core/colorspace.h \
    image/imagetile.h \
    image/imagelayer.h \
    image/image.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
