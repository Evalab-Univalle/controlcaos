#-------------------------------------------------
#
# Project created by QtCreator 2012-11-25T18:29:25
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -lGLU

TARGET = atractores
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lienzo.cpp \
    panel.cpp \
    numericmethods.cpp

HEADERS  += mainwindow.h \
    lienzo.h \
    panel.h \
    numericmethods.h \
    function.h

LIBS +=  -lGLU

FORMS += \
