QT += core network gui widgets

TARGET = QtSimpleChatClient
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += debug_and_release

SOURCES += \
    clientmain.cpp \
    chatwindow.cpp \
    chatclient.cpp \
    chatwithone.cpp

FORMS += \
    chatwindow.ui \
    chatwithone.ui

HEADERS += \
    chatwindow.h \
    chatclient.h \
    chatwithone.h
