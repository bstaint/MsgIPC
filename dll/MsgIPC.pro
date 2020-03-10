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

3rdparty += \
    debug/spdlog \
    debug/minhook \
    net/websocketpp \
    general/concurrentqueue

include (E:/3rdParty/3rdparty.pri)
include (E:/3rdParty/boost.pri)
