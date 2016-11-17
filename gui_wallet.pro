CONFIG += debug
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES += src/main_gui_wallet.cpp \
    src/gui_wallet_mainwindow.cpp \
    src/gui_wallet_centralwigdet.cpp \
    src/browse_content_tab.cpp
HEADERS += src/gui_wallet_mainwindow.h \
    src/gui_wallet_centralwigdet.h \
    src/browse_content_tab.h
