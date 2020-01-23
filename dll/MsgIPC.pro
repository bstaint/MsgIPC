TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        dllmain.cpp \
        qqdef.cpp

LIBS += -luser32

HEADERS += \
    precompiled.h \
    qqdef.h

PRECOMPILED_HEADER = precompiled.h

include (E:/3rdParty/extras/minhook.pri)
include (E:/3rdParty/debug/spdlog.pri)
include (E:/3rdParty/boost.pri)
include (E:/3rdParty/net/websocketpp.pri)
include (E:/3rdParty/extras/concurrentqueue.pri)
