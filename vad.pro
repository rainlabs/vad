#-------------------------------------------------
#
# Project created by QtCreator 2014-02-15T20:42:36
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = vad
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
LIBS += -lsfml-system -lsfml-audio -lsvm
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    signal.cpp \
    window.cpp \
    c_svm.cpp \
    mfcc.cpp

HEADERS += \
    signal.h \
    window.h \
    c_svm.h \
    mfcc.h
