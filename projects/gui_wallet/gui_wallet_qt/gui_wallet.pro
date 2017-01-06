# File gui_wallet.pro
#
# File created : 18 Nov 2016
# Created by   : Davit Kalantaryan (davit.kalantaryan@desy.de)
#
# This file can be used to produce Makefile for gui_wallet GUI application
# for Decent
#

#http://doc.qt.io/qt-5/osx-deployment.html
#CONFIG += TEST
# For making test: '$qmake "CONFIG+=TEST" gui_wallet.pro'  , then '$make'

options = $$find(CONFIG, "TEST")

count(options, 1) {

DEFINES += TEST_SIMPLE_APP
SOURCES += ../../../src/dgui/main_gui_wallet.cpp

}else{


DECENT_ROOT_DEFAULT = ../../../../DECENT-Network
USE_LIB_OR_NOT = not_use_lib

DECENT_ROOT_DEV = $$(DECENT_ROOT)
equals(DECENT_ROOT_DEV, ""): DECENT_ROOT_DEV = $$DECENT_ROOT_DEFAULT

DECENT_LIB = $$DECENT_ROOT_DEV/libraries

BOOST_ROOT_QT = $$(BOOST_ROOT)
#equals(BOOST_ROOT_QT, ""): BOOST_ROOT_QT = /usr/local/opt/boost
#equals(BOOST_ROOT_QT, ""): BOOST_ROOT_QT = ../../../../../opt/boost_1_57_0_unix
equals(BOOST_ROOT_QT, ""){
    exists( /usr/local/opt/boost/libboost_thread* ){
        BOOST_ROOT_QT = /usr/local/opt/boost
    }else{
        BOOST_ROOT_QT = ../../../../../opt/boost_1_57_0_unix
    }
}
message("!!!!!! BOOST_ROOT is '"$$BOOST_ROOT_QT"'")
#message("!!!!!! BOOST_ROOT is" $$(BOOST_ROOT))

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-variable
QMAKE_CXXFLAGS_WARN_ON += -Wno-sign-compare
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-function
QMAKE_CXXFLAGS_WARN_ON -= -Wunused-function

INCLUDEPATH += $$DECENT_LIB/wallet/include
INCLUDEPATH += $$DECENT_LIB/app/include
INCLUDEPATH += $$DECENT_LIB/encrypt/include

INCLUDEPATH += $$BOOST_ROOT_QT/include
INCLUDEPATH += $$DECENT_LIB/fc/include
INCLUDEPATH += $$DECENT_LIB/app/include
INCLUDEPATH += $$DECENT_LIB/chain/include
INCLUDEPATH += $$DECENT_LIB/db/include
INCLUDEPATH += $$DECENT_LIB/plugins/market_history/include
INCLUDEPATH += $$DECENT_LIB/net/include
INCLUDEPATH += $$DECENT_LIB/plugins/debug_witness/include
INCLUDEPATH += $$DECENT_LIB/egenesis/include
INCLUDEPATH += $$DECENT_LIB/utilities/include
INCLUDEPATH += $$DECENT_LIB/wallet/include
INCLUDEPATH += $$DECENT_LIB/fc/vendor/secp256k1-zkp/include
INCLUDEPATH += $$DECENT_LIB/fc/vendor/websocketpp
INCLUDEPATH += $$DECENT_LIB/fc/vendor/secp256k1-zkp
INCLUDEPATH += ../../../include

DEFINES += USE_NUM_GMP

win32{
    SYSTEM_PATH = ../../../sys/win64
    LIBS += -lcrypto++
}
else {
    macx{
        #QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12
        LIBS += -isysroot$(DEVELOPER_SDK_DIR)/MacOSX$(MACOSX_DEPLOYMENT_TARGET).sdk
        SYSTEM_PATH = ../../../sys/mac

        OPEN_SSL_ROOT_PATH = $$(OPENSSL_ROOT_DIR)
        equals(OPEN_SSL_ROOT_PATH, ""): OPEN_SSL_ROOT_PATH = /usr/local/opt/openssl

        CRIPTOPP_ROOT_PATH = $$(CRIPTOPP_ROOT_DIR)
        equals(CRIPTOPP_ROOT_PATH, ""): CRIPTOPP_ROOT_PATH = /usr/local/opt/cryptopp
        #CRIPTOPP_ROOT_PATH = $$CALLER_PATH/cryptopp/$$CRIPTOPP_VERSION

        #INCLUDEPATH += $$CALLER_PATH/openssl/1.0.2j/include
        INCLUDEPATH += $$OPEN_SSL_ROOT_PATH/include
        INCLUDEPATH += $$CRIPTOPP_ROOT_PATH/include
        LIBS += -L$$CRIPTOPP_ROOT_PATH/lib
        LIBS += -L$$OPEN_SSL_ROOT_PATH/lib
        LIBS += -lcryptopp
    }
    else{
        CODENAME = $$system(lsb_release -c | cut -f 2)
        SYSTEM_PATH = ../../../sys/$$CODENAME
        LIBS += -lcrypto++
    }
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

QMAKE_CXXFLAGS += -msse4.2
QMAKE_CFLAGS += -msse4.2

equals(USE_LIB_OR_NOT, "not_use_lib") {

message( "Preparing all object files localy..." )
LIBS += -L$$BOOST_ROOT_QT/lib

LIBS += $$DECENT_LIB/wallet/libgraphene_wallet.a
LIBS += $$DECENT_LIB/utilities/libgraphene_utilities.a
LIBS += $$DECENT_LIB/egenesis/libgraphene_egenesis_brief.a
LIBS += $$DECENT_LIB/app/libgraphene_app.a
LIBS += $$DECENT_LIB/chain/libgraphene_chain.a
LIBS += $$DECENT_LIB/contrib/pbc/.libs/libpbc.a
LIBS += $$DECENT_LIB/wallet/libgraphene_wallet.a
LIBS += $$DECENT_LIB/encrypt/libdecent_encrypt.a
LIBS += $$DECENT_LIB/contrib/fc/libfc_debug.a
LIBS += $$DECENT_LIB/contrib/fc/vendor/secp256k1-zkp/src/project_secp256k1-build/.libs/libsecp256k1.a

# http://askubuntu.com/questions/486006/cannot-find-boost-thread-mt-library

exists( $$BOOST_ROOT_QT/lib/libboost_thread-mt* ) {
      #message( "Configuring for multi-threaded Qt..." )
      #CONFIG += thread
    LIBS += -lboost_thread-mt
}else{
    LIBS += -lboost_thread
}

exists( $$BOOST_ROOT_QT/lib/libboost_context-mt* ) {
      #message( "Configuring for multi-threaded Qt..." )
      #CONFIG += thread
    LIBS += -lboost_context-mt
}else{
    LIBS += -lboost_context
}

LIBS += -lboost_system
LIBS += -lboost_chrono
LIBS += -lboost_coroutine
LIBS += -lboost_date_time
LIBS += -lboost_filesystem

#LIBS += -lgmp
LIBS += -lssl
LIBS += -lz
LIBS += -lcrypto

}else{
LIBS += -L$$SYSTEM_PATH/bin
LIBS += -llib_gui_wallet
}

SOURCES += ../../../src/dgui/main_gui_wallet.cpp \
    ../../../src/dgui/gui_wallet_mainwindow.cpp \
    ../../../src/dgui/gui_wallet_centralwigdet.cpp \
    ../../../src/dgui/browse_content_tab.cpp \
    ../../../src/dgui/transactions_tab.cpp \
    ../../../src/dgui/upload_tab.cpp \
    ../../../src/dgui/overview_tab.cpp \
    ../../../src/dgui/gui_wallet_global.cpp \
    ../../../src/dgui/gui_wallet_connectdlg.cpp \
    ../../../src/dgui/fc_rpc_gui.cpp \
    ../../../src/dgui/gui_wallet_application.cpp
HEADERS += ../../../src/dgui/gui_wallet_mainwindow.hpp \
    ../../../src/dgui/gui_wallet_centralwigdet.hpp \
    ../../../src/dgui/browse_content_tab.hpp \
    ../../../src/dgui/transactions_tab.hpp \
    ../../../src/dgui/upload_tab.hpp \
    ../../../src/dgui/overview_tab.hpp \
    ../../../src/dgui/gui_wallet_global.hpp \
    ../../../src/dgui/gui_wallet_connectdlg.hpp \
    ../../../src/dgui/fc_rpc_gui.hpp \
    ../../../include/unnamedsemaphorelite.hpp \
    ../../../src/dgui/gui_wallet_application.hpp \
    ../../../src/dgui/connected_api_instance.hpp

}

SOURCES += \
    ../../../src/dgui/text_display_dialog.cpp \
    ../../../src/dgui/walletcontentdlg.cpp

HEADERS += \
    ../../../src/dgui/text_display_dialog.hpp \
    ../../../src/dgui/walletcontentdlg.hpp
