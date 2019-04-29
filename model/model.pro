TEMPLATE = lib
#CONFIG += staticlib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

QT += network networkauth

SOURCES += \
        playingqueue.cpp \
        playlist.cpp \
        query.cpp \
        session.cpp \
        track.cpp \
        user.cpp

HEADERS += \
    playingqueue.h \
    playlist.h \
    query.h \
    session.h \
    track.h \
    user.h

