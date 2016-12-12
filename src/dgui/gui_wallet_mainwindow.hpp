/*
 *	File: gui_wallet_mainwindow.cpp
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
#include "gui_wallet_centralwigdet.hpp"
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

    protected slots:
        void AboutSlot();

    private:
        class QVBoxLayout*   m_pCentralAllLayout;
        class QHBoxLayout*   m_pMenuLayout;
        CentralWigdet*       m_pCentralWidget;

        QMenuBar *      m_barLeft ;
        QMenuBar *      m_barRight;
        QMenu*          m_pMenuFile;
        QMenu*          m_pMenuSetting;
        QMenu*          m_pMenuHelpL;
        QMenu*          m_pMenuContent;
        QMenu*          m_pMenuHelpR;
        QMenu*          m_pMenuCreateTicket;
        QAction         m_ActionExit;
        QAction         m_ActionAbout;
    };

}

#endif // MAINWINDOW_GUI_WALLET_H
