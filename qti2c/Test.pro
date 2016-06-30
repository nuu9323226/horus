#-------------------------------------------------
#
# Project created by QtCreator 2016-05-26T09:11:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    I2C_Thread.cpp

HEADERS  += mainwindow.h \
    delay.h \
    I2C_Thread.h

FORMS    += mainwindow.ui
