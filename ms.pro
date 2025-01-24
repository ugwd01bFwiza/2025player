QT += core gui dtkwidget

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ms
TEMPLATE = app

SOURCES +=src/main.cpp \
      src/gui/mainwindow.cpp \
      src/gui/navwidget.cpp \
    src/gui/controlbar.cpp

RESOURCES +=         resources.qrc
INCLUDEPATH += $$PWD/src/include

HEADERS +=src/include/mainwindow.h \
    src/include/navwidget.h \
    src/include/controlbar.h

DISTFILES +=

debug {
    DESTDIR = build/debug/
}

release {
    DESTDIR = build/release/
}
