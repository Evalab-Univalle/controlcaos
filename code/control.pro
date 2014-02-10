#-------------------------------------------------
#
# Project created by QtCreator 2013-04-08T14:10:17
#
#-------------------------------------------------

QT       += core gui

CONFIG += qwt

TARGET = control
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    canvas.cpp \
    serie.cpp \
    algoritmo.cpp \
    matematica.cpp

HEADERS  += mainwindow.h \
    board.h \
    canvas.h \
    serie.h \
    algoritmo.h \
    definitions.h \
    matematica.h

FORMS    += mainwindow.ui \
    board.ui \
    canvas.ui
