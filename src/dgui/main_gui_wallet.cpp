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
#include <string.h>
#include <QApplication>
#include "gui_wallet_mainwindow.hpp"

int g_nDebugApplication = 0;


int main(int argc, char* argv[])
{
    for(int i(1); i<argc;)
    {
        if((strcmp(argv[i],"--debug-application")==0)||(strcmp(argv[i],"-dba")==0))
        {
            if (i<(--argc))
            {
                memmove(argv+i,argv+i+1,(argc-i)*sizeof(char*));
                g_nDebugApplication = atoi(argv[i]);
                if (i<(--argc)){memmove(argv+i,argv+i+1,(argc-i)*sizeof(char*));}
            }
        }
        else if((strcmp(argv[i],"--bgr-color")==0)||(strcmp(argv[i],"-b")==0))
        {
            if (i<(--argc))
            {
                memmove(argv+i,argv+i+1,(argc-i)*sizeof(char*));
                // ...
            }
        }
        else
        {
            ++i;
        }
    }

    freopen( "/dev/null", "w", stderr);
    QApplication aApp(argc,argv);
    gui_wallet::Mainwindow_gui_wallet aMainWindow;

    aMainWindow.show();

    aApp.exec();

    return 0;
}

