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
        m_ActionExit(tr("&Exit"),this),
        m_ActionAbout(tr("About"),this)
{
#if 0

    setCentralWidget(&m_CentralWidget);
    CreateActions();
    CreateMenues();
    resize(900,550);

#else

    m_barLeft = new QMenuBar;
    m_barRight = new QMenuBar;

    m_pCentralAllLayout = new QVBoxLayout;
    m_pMenuLayout = new QHBoxLayout;

    m_pMenuLayout->addWidget(m_barLeft);
    m_pMenuLayout->addWidget(m_barRight);

    m_pMenuLayout->setAlignment(m_barLeft, Qt::AlignLeft);
    m_pMenuLayout->setAlignment(m_barRight, Qt::AlignRight);

    m_pCentralAllLayout->addLayout(m_pMenuLayout);
    /*mainMenuLayout0->addWidget(new QWidget);

    QWidget *central = new QWidget;
    central->setLayout(mainMenuLayout0);*/

    m_pCentralWidget = new CentralWigdet(m_pCentralAllLayout);
    m_pCentralWidget->setLayout(m_pCentralAllLayout);
    setCentralWidget(m_pCentralWidget);
    CreateActions();
    CreateMenues();
    resize(900,550);

    setCentralWidget(m_pCentralWidget);

#endif
}


Mainwindow_gui_wallet::~Mainwindow_gui_wallet()
{
}


void Mainwindow_gui_wallet::AboutSlot()
{}


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

    m_ActionAbout.setStatusTip( tr("About") );
    connect( &m_ActionAbout, SIGNAL(triggered()), this, SLOT(AboutSlot()) );

    /**************************************************************************/

    /**************************************************************************/

    /**************************************************************************/
}


void Mainwindow_gui_wallet::CreateMenues()
{
    QMenuBar* pMenuBar = m_barLeft;

    m_pMenuFile = pMenuBar->addMenu( tr("&File") );
    //m_pMenuFile->addAction( m_pActionLoadIniFile );
    //m_pMenuFile->addAction( m_pActionPrint );
    m_pMenuFile->addAction( &m_ActionExit );

    m_pMenuSetting = pMenuBar->addMenu( tr("&Setting") );
    m_pMenuHelpL = pMenuBar->addMenu( tr("&Help") );
    m_pMenuHelpL->addAction( &m_ActionAbout );
    m_pMenuContent = pMenuBar->addMenu( tr("Content") );

    //QMenu*          m_pMenuHelpR;
    //QMenu*          m_pMenuCreateTicket;
    pMenuBar = m_barRight;
    m_pMenuHelpR = pMenuBar->addMenu( tr("Help") );
    m_pMenuHelpR->addAction( &m_ActionAbout );
    m_pMenuCreateTicket = pMenuBar->addMenu( tr("Create ticket") );
}
