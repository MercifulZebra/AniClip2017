#-------------------------------------------------
#
# Project created by QtCreator 2017-01-14T13:08:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AniClip2017
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logger.cpp \
    clipinfoedit.cpp \
    autocompleteredit.cpp \
    clipdatabase.cpp \
    videocontrols.cpp

HEADERS  += mainwindow.h \
    logger.h \
    clipinfoedit.h \
    autocompleteredit.h \
    clipdatabase.h \
    videocontrols.h

FORMS    += mainwindow.ui \
    clipinfoedit.ui \
    videocontrols.ui

DISTFILES += \
    aniclip_config.txt
