# File gui_wallet.pro
#
# File created : 18 Nov 2016
# Created by   : Davit Kalantaryan (davit.kalantaryan@desy.de)
#
# This file can be used to produce Makefile for gui_wallet GUI application
# for Decent
#

BOOST_ROOT= ../../../../../opt/boost_1_57_0_unix
DECENT_ROOT = ../../../../DECENT-Network
DECENT_LIB = $$DECENT_ROOT/libraries

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-variable
QMAKE_CXXFLAGS_WARN_ON += -Wno-sign-compare
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-function
QMAKE_CXXFLAGS_WARN_ON -= -Wunused-function

INCLUDEPATH += $$DECENT_LIB/wallet/include
INCLUDEPATH += $$DECENT_LIB/app/include
INCLUDEPATH += $$DECENT_LIB/encrypt/include

INCLUDEPATH += $$BOOST_ROOT/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/fc/include
INCLUDEPATH +=  ../../../../DECENT-Network/libraries/app/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/chain/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/db/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/plugins/market_history/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/net/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/plugins/debug_witness/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/egenesis/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/utilities/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/wallet/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/fc/vendor/secp256k1-zkp/include
INCLUDEPATH += ../../../../DECENT-Network/libraries/fc/vendor/websocketpp
INCLUDEPATH += ../../../../DECENT-Network/libraries/fc/vendor/secp256k1-zkp

DEFINES += USE_NUM_GMP

win32:SYSTEM_PATH = ../../../sys/win64
else { 
    CODENAME = $$system(lsb_release -c | cut -f 2)
    SYSTEM_PATH = ../../../sys/$$CODENAME
}

# Debug:DESTDIR = debug1
DESTDIR = $$SYSTEM_PATH/bin
OBJECTS_DIR = $$SYSTEM_PATH/.objects
CONFIG += debug
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
#QT -= core
#QT -= gui
#QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
SOURCES += ../../../src/dgui/main_gui_wallet.cpp \
    ../../../src/dgui/gui_wallet_mainwindow.cpp \
    ../../../src/dgui/gui_wallet_centralwigdet.cpp \
    ../../../src/dgui/browse_content_tab.cpp \
    ../../../src/dgui/transactions_tab.cpp \
    ../../../src/dgui/upload_tab.cpp \
    ../../../src/dgui/overview_tab.cpp \
    ../../../src/dgui/gui_wallet_global.cpp
HEADERS += ../../../src/dgui/gui_wallet_mainwindow.hpp \
    ../../../src/dgui/gui_wallet_centralwigdet.hpp \
    ../../../src/dgui/browse_content_tab.hpp \
    ../../../src/dgui/transactions_tab.hpp \
    ../../../src/dgui/upload_tab.hpp \
    ../../../src/dgui/overview_tab.hpp \
    ../../../src/dgui/gui_wallet_global.hpp
