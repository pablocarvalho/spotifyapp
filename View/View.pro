#-------------------------------------------------
#
# Project created by QtCreator 2019-04-22T18:44:22
#
#-------------------------------------------------

QT       += core gui webenginewidgets network networkauth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = View
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
#        searchareawidget.cpp \
    newplaylistdialog.cpp \
    playlistarea.cpp \
    playlistitem.cpp \
    playlisttracksarea.cpp \
    playlisttrackwidget.cpp \
        searchresultsarea.cpp \
        searchresultwidget.cpp

HEADERS += \
        mainwindow.h \
#        searchareawidget.h \
    newplaylistdialog.h \
    playlistarea.h \
    playlistitem.h \
    playlisttracksarea.h \
    playlisttrackwidget.h \
        searchresultsarea.h \
        searchresultwidget.h

FORMS += \
        mainwindow.ui \
#        searchareawidget.ui \
    newplaylistdialog.ui \
    playlistarea.ui \
    playlisttracksarea.ui \
    playlisttrackwidget.ui \
        searchresultsarea.ui \
        searchresultwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../Controller
DEPENDPATH += $$PWD/../Controller
LIBS += -L"../Controller"
LIBS += -lController
LIBS += -L"../model"
LIBS += -lmodel
INCLUDEPATH += ../model
DEPENDPATH += $$PWD/../model

DISTFILES +=

RESOURCES += \
    resources.qrc
