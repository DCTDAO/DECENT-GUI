/*
 *	File: mainwindow_gui_wallet.cpp
 *
 *	Created on: Nov 11, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef MAINWINDOW_GUI_WALLET_H
#define MAINWINDOW_GUI_WALLET_H

#include <QMainWindow>
#include "gui_wallet_centralwigdet.h"
#include <QAction>

namespace gui_wallet
{

    //class Mainwindow_gui_wallet : public QMainWindow
    class Mainwindow_gui_wallet : public QMainWindow
    {
    public:
        Mainwindow_gui_wallet();
        virtual ~Mainwindow_gui_wallet();   // virtual because may be this class will be
                                            // used by inheritance
        void CreateActions();
        void CreateMenues();

    private:
        CentralWigdet   m_CentralWidget;
        QMenu*          m_pMenuFile;
        QMenu*          m_pMenuSetting;
        QMenu*          m_pMenuHelp;
        QMenu*          m_pMenuContent;
        QAction         m_ActionExit;
    };

}

#endif // MAINWINDOW_GUI_WALLET_H
