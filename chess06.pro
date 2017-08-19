#-------------------------------------------------
#
# Project created by QtCreator 2017-05-11T20:52:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess06
TEMPLATE = app


SOURCES += main.cpp\
    overwidget.cpp \
    startwidget.cpp \
    widget.cpp

HEADERS  += widget.h \
    overwidget.h \
    startwidget.h

FORMS    += widget.ui \
    overwidget.ui \
    startwidget.ui

OTHER_FILES +=

RESOURCES += \
    image.qrc

CONFIG +=C++11
