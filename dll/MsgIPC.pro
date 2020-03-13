TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        dllmain.cpp \
        message.cpp \
        qq_definition.cpp \
        websocket_client.cpp

HEADERS += \
    message.h \
    precompiled.h \
    qq_definition.h \
    websocket_client.h

PRECOMPILED_HEADER = precompiled.h

LIBS += -luser32

include (E:/3rdParty/boost.pri)
include (E:/3rdParty/3rdparty.pri)

add_deps(debug/spdlog)
add_deps(debug/minhook)
add_deps(net/websocketpp)
add_deps(general/concurrentqueue)
