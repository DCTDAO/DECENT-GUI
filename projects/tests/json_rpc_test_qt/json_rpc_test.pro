# File gui_wallet.pro
#
# File created : 24Nov 2016
# Created by   : Davit Kalantaryan (davit.kalantaryan@desy.de)
#
# This file can be used to produce Makefile for json_rpc_test application
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

# greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
QT -= core
QT -= gui
SOURCES += ../../../src/tests/main_json_rpc_test.cpp
