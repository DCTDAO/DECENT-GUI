/*
 *	File: gui_wallet_mainwindow.cpp
 *
 *	Created on: Nov 11, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#include "gui_wallet_mainwindow.hpp"
#include <QMenuBar>

using namespace gui_wallet;

Mainwindow_gui_wallet::Mainwindow_gui_wallet()
        :
        m_ActionExit(tr("&Exit"),this)
{
    setCentralWidget(&m_CentralWidget);
    CreateActions();
    CreateMenues();
    resize(800,300);
}


Mainwindow_gui_wallet::~Mainwindow_gui_wallet()
{
}


void Mainwindow_gui_wallet::CreateActions()
{
    //m_pActionLoadIniFile = new QAction( tr("&Load ini"), this );
    //m_pActionLoadIniFile->setIcon( QIcon(":/images/open.png") );
    //m_pActionLoadIniFile->setShortcut( QKeySequence::Open );
    //m_pActionLoadIniFile->setStatusTip( tr("Load ini file") );
    //connect( m_pActionLoadIniFile, SIGNAL(triggered()), this, SLOT(LoadIniFileSlot()) );

    /**************************************************************************///m_pActionPrint

    //m_pActionPrint = new QAction( tr("&Print"), this );
    //m_pActionLoadIniFile->setIcon( QIcon(":/images/open.png") );
    //m_pActionLoadIniFile->setShortcut( QKeySequence::Open );
    //m_pActionPrint->setStatusTip( tr("Print") );
    //connect( m_pActionLoadIniFile, SIGNAL(triggered()), this, SLOT(LoadIniFileSlot()) );

    /**************************************************************************///m_pActionGuiConf

    m_ActionExit.setStatusTip( tr("Exit Program") );
    connect( &m_ActionExit, SIGNAL(triggered()), this, SLOT(close()) );

    /**************************************************************************/

    /**************************************************************************/

    /**************************************************************************/

    /**************************************************************************/
}


void Mainwindow_gui_wallet::CreateMenues()
{
    m_pMenuFile = menuBar()->addMenu( tr("&File") );
    //m_pMenuFile->addAction( m_pActionLoadIniFile );
    //m_pMenuFile->addAction( m_pActionPrint );
    m_pMenuFile->addAction( &m_ActionExit );

    m_pMenuSetting = menuBar()->addMenu( tr("&Setting") );
    m_pMenuHelp = menuBar()->addMenu( tr("&Help") );
    m_pMenuContent = menuBar()->addMenu( tr("Content") );
}
