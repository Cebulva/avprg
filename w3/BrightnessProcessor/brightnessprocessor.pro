#-------------------------------------------------
#
# Project created by QtCreator 2014-07-15T19:38:24
#
#-------------------------------------------------

QT       += core gui widgets



TARGET = VideoPlayer
TEMPLATE = app


SOURCES += main.cpp\
        videoplayer.cpp \
    brightnessprocessor.cpp

HEADERS  += videoplayer.h \
    brightnessprocessor.h

FORMS    += videoplayer.ui

include(../videoengine/videoengine.pri)
