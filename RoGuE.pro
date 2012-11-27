#-------------------------------------------------
#
# Project created by QtCreator 2012-11-26T18:48:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoGuE
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    rmlsyntaxhighlighter.cpp

HEADERS  += mainwindow.hpp \
    rmlsyntaxhighlighter.hpp

FORMS    += mainwindow.ui
