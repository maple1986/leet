TEMPLATE = app
CONFIG += console c++11
QMAKE_CXXFLAGS += -std=c++0x
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    NumofOnes.cpp \
    bfs.cpp \
    backtrack.cpp \
    stringrel.cpp \
    powerofn.cpp \
    sortrel.cpp \
    ZigZag6.cpp \
    myatoi.cpp \
    dfs.cpp \
    balancetree.cpp \
    msra.cpp \
    listsolutions.cpp \
    bitsrel.cpp \
    MinStack.cpp \
    sortalg.cpp \
    hashrel.cpp \
    binarysearchrel.cpp \
    easy.cpp \
    mathrel.cpp \
    greedy.cpp \
    dprel.cpp \
    divideandconquer.cpp \
    nsum.cpp

HEADERS += \
    NumofOnes.h \
    bfs.h \
    backtrack.h \
    stringrel.h \
    powerofn.h \
    sortrel.h \
    ZigZag6.h \
    myatoi.h \
    dfs.h \
    balancetree.h \
    msra.h \
    listsolutions.h \
    StringRel.h \
    bitsrel.h \
    MinStack.h \
    sortalg.h \
    hashrel.h \
    binarysearchrel.h \
    easy.h \
    mathrel.h \
    greedy.h \
    dprel.h \
    divideandconquer.h \
    nsum.h
