QT += core network gui widgets

TARGET = QtSimpleChatClient
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += debug_and_release

SOURCES += \
    clientmain.cpp \
    chatwindow.cpp \
    chatclient.cpp \
    chatwithone.cpp \
    chatwithgroup.cpp

FORMS += \
    chatwindow.ui \
    chatwithone.ui \
    chatwithgroup.ui

HEADERS += \
    chatwindow.h \
    chatclient.h \
    chatwithone.h \
    chatwithgroup.h
