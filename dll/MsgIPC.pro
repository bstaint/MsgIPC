TEMPLATE = lib
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        pushserver.cpp \
        qqdef.cpp
        
HEADERS += \
    pushserver.h \
    qqdef.h

LIBS += -luser32

include(E:/3rdParty/extras/minhook.pri)
include(E:/3rdParty/net/cppzmq.pri)
include(E:/3rdParty/net/msgpack.pri)
include(E:/3rdParty/debug/spdlog.pri)