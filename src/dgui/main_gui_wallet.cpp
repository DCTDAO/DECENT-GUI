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
#include <wchar.h>
#include <string.h>
#ifndef TEST_SIMPLE_APP
#include "gui_wallet_application.hpp"
#include "gui_wallet_mainwindow.hpp"
#endif

int g_nDebugApplication = 0;

int main(int argc, char* argv[])
{

#ifdef TEST_SIMPLE_APP
    printf("Hello world! argc=%d, argv=%p\n",argc,argv);
#else
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
    gui_wallet::application aApp(argc,argv);

#if 0
    //QString testString;
    wprintf(L"fwide=%d\n",fwide(stdout,1));
    wprintf(L"Русский\n");
    wchar_t i = 0x2192;
    //for( i=4000; i<6000;++i)
    {
        //wprintf(L"chr=%c(code=%d)\n",i,(int)i);
        wprintf(L"chr='%lc'(code=%d)\n",i,(int)i);
    }
#else
    gui_wallet::Mainwindow_gui_wallet aMainWindow;
    aMainWindow.show();
    aApp.exec();
#endif
#endif

    return 0;
}

