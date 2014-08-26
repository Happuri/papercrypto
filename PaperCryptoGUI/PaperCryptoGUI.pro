#-------------------------------------------------
#
# Project created by QtCreator 2013-12-10T09:26:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaperCryptoGUI
TEMPLATE = app


SOURCES += main.cpp\
        papercrypto_gui.cpp \
    cotp.cpp

HEADERS  += papercrypto_gui.h \
    cotp.h

FORMS    += papercrypto_gui.ui

OTHER_FILES += \
    icon.svg
