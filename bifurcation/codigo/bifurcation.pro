#-------------------------------------------------
#
# Project created by QtCreator 2013-02-17T12:50:39
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -lGLU

TARGET = bifurcation

TEMPLATE = app

SOURCES += main.cpp \
    canvas.cpp \
    numericmethods.cpp \
    choice.cpp

HEADERS += \
    canvas.h \
    numericmethods.h \
    function.h \
    choice.h

FORMS += \
    choice.ui
