QT += core gui dtkwidget
QT += multimedia
QT += quick
INCLUDEPATH += /usr/include/taglib /usr/include/taglib-extras

LIBS += -L/usr/lib -ltag

QMAKE_CXXFLAGS += -I /usr/include/taglib -I /usr/include/taglib-extras
QMAKE_LIBS += -ltag

QMAKE_PKGCONFIG_LIBDIR += ./src/thirdparty/ffmpeg/lib/pkgconfig
CONFIG += link_pkgconfig
PKGCONFIG += libavcodec libavdevice libavfilter libavformat libavutil libswresample libswscale

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ms
TEMPLATE = app

SOURCES +=src/main.cpp \
      src/gui/mainwindow.cpp \
      src/gui/navwidget.cpp \
    src/gui/controlbar.cpp \
    src/gui/musictable.cpp \
    src/play/musicplayer.cpp


RESOURCES += resources.qrc

INCLUDEPATH += $$PWD/src/include
INCLUDEPATH += $$PWD/src/thirdparty/ffmpeg/include

HEADERS +=src/include/mainwindow.h \
    src/include/navwidget.h \
    src/include/controlbar.h \
    src/include/musictable.h \
    src/include/musicplayer.h \
    thirdparty/ffmpeg/include/*.h

DISTFILES +=

debug{
DESTDIR = build/debug/
}
release{
DESTDIR = build/release/
}



