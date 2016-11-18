# File gui_wallet.pro
# File created: Nov 18 2016
# Created by  : Davit Kalantaryan (davit.kalantaryan@desy.de)
#
# This file can be used to produce Makefile for gui_wallet GUI application
# for Decent
#

win32 {
SYSTEM_PATH = ../../../systems/win64
}else{
CODENAME = $$system(lsb_release -c | cut -f 2)
SYSTEM_PATH = ../../../systems/$$CODENAME
}
#Debug:DESTDIR = debug1
DESTDIR = $$SYSTEM_PATH/bin
OBJECTS_DIR = $$SYSTEM_PATH/.objects
CONFIG += debug
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES += ../../../src/main_gui_wallet.cpp \
    ../../../src/gui_wallet_mainwindow.cpp \
    ../../../src/gui_wallet_centralwigdet.cpp \
    ../../../src/browse_content_tab.cpp
HEADERS += ../../../src/gui_wallet_mainwindow.h \
    ../../../src/gui_wallet_centralwigdet.h \
    ../../../src/browse_content_tab.h
    
