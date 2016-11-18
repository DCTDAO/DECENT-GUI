/*
 *	File: main_gui_wallet.cpp
 *
 *	Created on: Nov 11, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */

#include <stdio.h>
#include <QApplication>
#include "gui_wallet_mainwindow.h"


int main(int argc, char* argv[])
{
    freopen( "/dev/null", "w", stderr);
    QApplication aApp(argc,argv);
    gui_wallet::Mainwindow_gui_wallet aMainWindow;

    aMainWindow.show();

    aApp.exec();

    return 0;
}

