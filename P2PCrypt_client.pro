#-------------------------------------------------
#
# Project created by QtCreator 2013-03-14T10:54:11
#
#-------------------------------------------------

QT       += core gui concurrent network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = P2PCrypt_client
TEMPLATE = app

#Remeber to change this per computer and version change
DESTDIR = /home/qt_dev/p2pcrypt_client/v0.0.3/P2PCrypt_client/

SOURCES += main.cpp \
    p2pcrypt_startup.cpp \
    p2pcrypt_algo.cpp \
    p2pcrypt_sql.cpp

HEADERS  += \
    p2pcrypt_startup.h \
    p2pcrypt_algo.h \
    p2pcrypt_sql.h

LIBS += -lssl
LIBS += -lcrypto

OTHER_FILES += \
    README.md
