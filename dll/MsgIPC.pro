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

include (E:/3rdParty/extras/minhook.pri)
include (E:/3rdParty/debug/spdlog.pri)
include (E:/3rdParty/boost.pri)
include (E:/3rdParty/net/websocketpp.pri)
include (E:/3rdParty/extras/concurrentqueue.pri)
