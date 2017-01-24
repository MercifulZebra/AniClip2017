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
    videocontrols.cpp \
    addtextscreen.cpp \
    viewscreen.cpp \
    viewshowscreen.cpp \
    rotatedbutton.cpp \
    debugwidget.cpp \
    tagtreewidget.cpp

HEADERS  += mainwindow.h \
    logger.h \
    clipinfoedit.h \
    autocompleteredit.h \
    clipdatabase.h \
    videocontrols.h \
    debugwidget.h \
    addtextscreen.h \
    viewscreen.h \
    viewshowscreen.h \
    rotatedbutton.h \
    tagtreewidget.h

FORMS    += mainwindow.ui \
    clipinfoedit.ui \
    videocontrols.ui \
    debugwidget.ui \
    addtextscreen.ui \
    viewscreen.ui \
    viewshowscreen.ui

DISTFILES += \
    aniclip_config.txt
