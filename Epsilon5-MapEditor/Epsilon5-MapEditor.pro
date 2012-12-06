QT += core gui

TARGET = Epsilon5-MapEditor
TEMPLATE = app

SOURCES += \
    ../utils/uexception.cpp \
    ../utils/usettings.cpp \
    ../utils/ucast.cpp \
    main.cpp \
    mainwindow.cpp \
#    createmapdialog.cpp \
#    mapcreator.cpp \
#    graphicsview.cpp \
#    mapitem.cpp \
#    utils.cpp \
#    openmapdialog.cpp \
#    mapitemsignal.cpp \
    settings.cpp \
    application.cpp \
    ui/configurationdialog.cpp \
    ui/objectseditorform.cpp \
    imagecache.cpp \
    containers/container.cpp \
    containers/mapcontainer.cpp \
    containers/structures.cpp \
    containers/mapobjectcontainer.cpp \
    containers/maprespawncontainer.cpp \
    containers/mapitem.cpp \
    containers/mapobjectitem.cpp \
    containers/maprespawnitem.cpp

HEADERS += \
    ../utils/uexception.h \
    ../utils/usettings.h \
    ../utils/ucast.h \
    mainwindow.h \
#    createmapdialog.h \
#    mapcreator.h \
#    graphicsview.h \
#    mapitem.h \
#    utils.h \
#    openmapdialog.h \
#    mapitemsignal.h \
    application.h \
    settings.h \
    global.h \
    ui/configurationdialog.h \
    ui/objectseditorform.h \
    imagecache.h \
    containers/container.h \
    containers/mapcontainer.h \
    containers/mapobjectcontainer.h \
    containers/maprespawncontainer.h \
    containers/mapitem.h \
    containers/mapobjectitem.h \
    containers/maprespawnitem.h \
    containers/structures.h

FORMS += \
#    createmapdialog.ui \
#    openmapdialog.ui \
    ui/configurationdialog.ui \
    ui/objectseditorform.ui

QMAKE_CXXFLAGS += -std=c++0x
# -mfpmath=sse
# -Ofast -flto -funroll-loops
