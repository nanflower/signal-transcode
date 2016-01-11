#-------------------------------------------------
#
# Project created by QtCreator 2016-01-11T11:28:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = signal-transcode
TEMPLATE = app

INCLUDEPATH += /opt/intel/mediasdk/include
INCLUDEPATH += /usr/local/include
LIBS     += -lavcodec -lavfilter -lavformat -lavutil -lswresample -lswscale
LIBS +=  -L/usr/local/lib/ -lfaac -L/usr/local/

SOURCES += main.cpp\
        mainwindow.cpp \
    udp.cpp \
    udpsocket.cpp \
    tspoolqueue.cpp \
    transcodepool.cpp

HEADERS  += mainwindow.h \
    udp.h \
    udpsocket.h \
    tspoolqueue.h \
    transcodepool.h

FORMS    += mainwindow.ui
