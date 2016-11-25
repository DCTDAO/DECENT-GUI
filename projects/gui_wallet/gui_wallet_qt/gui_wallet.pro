# File gui_wallet.pro
#
# File created : Nov 18 2016
# Created by   : Davit Kalantaryan (davit.kalantaryan@desy.de)
#
# This file can be used to produce Makefile for gui_wallet GUI application
# for Decent
#
win32:SYSTEM_PATH = ../../../sys/win64
else { 
    CODENAME = $$system(lsb_release -c | cut -f 2)
    SYSTEM_PATH = ../../../sys/$$CODENAME
}

# Debug:DESTDIR = debug1
DESTDIR = $$SYSTEM_PATH/bin
OBJECTS_DIR = $$SYSTEM_PATH/.objects
CONFIG += debug
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
#QT -= core
#QT -= gui
SOURCES += ../../../src/dgui/main_gui_wallet.cpp \
    ../../../src/dgui/gui_wallet_mainwindow.cpp \
    ../../../src/dgui/gui_wallet_centralwigdet.cpp \
    ../../../src/dgui/browse_content_tab.cpp \
    ../../../src/dgui/transactions_tab.cpp \
    ../../../src/dgui/upload_tab.cpp \
    ../../../src/dgui/overview_tab.cpp
HEADERS += ../../../src/dgui/gui_wallet_mainwindow.hpp \
    ../../../src/dgui/gui_wallet_centralwigdet.hpp \
    ../../../src/dgui/browse_content_tab.hpp \
    ../../../src/dgui/transactions_tab.hpp \
    ../../../src/dgui/upload_tab.hpp \
    ../../../src/dgui/overview_tab.hpp
