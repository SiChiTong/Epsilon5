QT += core gui

TARGET = EpsMapGen
TAMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    createmapdialog.cpp \
    mapcreator.cpp \
    graphicsview.cpp \
    mapitem.cpp \
    utils.cpp

HEADERS += \
    mainwindow.h \
    createmapdialog.h \
    mapcreator.h \
    graphicsview.h \
    mapitem.h \
    utils.h

FORMS += \
    createmapdialog.ui

QMAKE_CXXFLAGS += -std=c++0x -mfpmath=sse -Ofast -flto -funroll-loops
