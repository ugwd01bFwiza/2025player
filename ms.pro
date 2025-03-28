QT += core gui dtkwidget
QT += multimedia multimediawidgets
QT += sql
INCLUDEPATH += /usr/include/taglib 

LIBS += -L/usr/lib -ltag


QMAKE_CXXFLAGS += -I /usr/include/taglib 
QMAKE_LIBS += -ltag


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ms
TEMPLATE = app

SOURCES +=src/main.cpp \
      src/gui/mainwindow.cpp \
      src/gui/navwidget.cpp \
    src/gui/controlbar.cpp \
    src/gui/musictable.cpp \
src/play/database.cpp\
    src/play/musicplayer.cpp \
    src/play/metadata.cpp \
    src/gui/settingsmanager.cpp \
    src/gui/pathselector.cpp\
    src/gui/shortcutmanager.cpp\
src/gui/settingpage.cpp \
    src/gui/videoplayer.cpp

RESOURCES += resources.qrc
INCLUDEPATH += $$PWD/src/include

HEADERS +=src/include/mainwindow.h \
    src/include/navwidget.h \
    src/include/controlbar.h \
    src/include/musictable.h \
    src/include/musicplayer.h\
src/include/database.h \
    src/include/metadata.h \
    src/include/settingsmanager.h \
    src/include/shortcutmanager.h\
    src/include/pathselector.h\
src/include/settingpage.h \
    src/include/videoplayer.h
DISTFILES +=

debug{
DESTDIR = build/debug/
}
release{
DESTDIR = build/release/
}



