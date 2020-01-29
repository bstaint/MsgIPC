TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        dllmain.cpp \
        message.cpp \
        qq_definition.cpp \
        websocket_client.cpp

LIBS += -luser32

HEADERS += \
    message.h \
    precompiled.h \
    qq_definition.h \
    websocket_client.h

PRECOMPILED_HEADER = precompiled.h

generals += \
        debug/spdlog

include (E:/3rdParty/boost.pri)
include (E:/3rdParty/debug/minhook.pri)
include (E:/3rdParty/net/websocketpp.pri)
include (E:/3rdParty/general/concurrentqueue.pri)
include (E:/3rdParty/general.pri)
