#-------------------------------------------------
#
# Project created by QtCreator 2013-03-14T10:54:11
#
#-------------------------------------------------

QT       += core gui concurrent network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = P2PCrypt_client
TEMPLATE = app


SOURCES += main.cpp \
    p2pcrypt_startup.cpp \
    p2pcrypt_algo.cpp

HEADERS  += \
    p2pcrypt_startup.h \
    p2pcrypt_algo.h

LIBS += -lssl
LIBS += -lcrypto
