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
#include "connected_api_instance.hpp"

using namespace gui_wallet;

Mainwindow_gui_wallet::Mainwindow_gui_wallet()
        :
        m_ActionExit(tr("&Exit"),this),
        m_ActionConnect(tr("Connect"),this),
        m_ActionAbout(tr("About"),this),
        m_ActionInfo(tr("Info"),this),
        m_ActionHelp(tr("Help"),this),
        m_ConnectDlg(this),
        m_info_dialog()
{
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

    m_info_dialog.resize(0,0);

    connect(this, SIGNAL(TaskDoneSig(int,std::string, std::string)), this, SLOT(TaskDoneSlot(int,std::string, std::string)) );

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

    m_ActionAbout.setStatusTip( tr("About") );
    connect( &m_ActionAbout, SIGNAL(triggered()), this, SLOT(AboutSlot()) );

    m_ActionHelp.setStatusTip( tr("Help") );
    connect( &m_ActionHelp, SIGNAL(triggered()), this, SLOT(HelpSlot()) );

    m_ActionInfo.setStatusTip( tr("Info") );
    connect( &m_ActionInfo, SIGNAL(triggered()), this, SLOT(InfoSlot()) );

    m_ActionConnect.setStatusTip( tr("Connect to witness node") );
    connect( &m_ActionConnect, SIGNAL(triggered()), this, SLOT(ConnectSlot()) );

    /**************************************************************************/

    /**************************************************************************/

    /**************************************************************************/
}




void Mainwindow_gui_wallet::CreateMenues()
{
#define ADD_ACTION_TO_MENU_HELP(__action_ptr__) \
    do{m_pMenuHelpL->addAction( (__action_ptr__) );m_pMenuHelpR->addAction( (__action_ptr__) );}while(0)

    QMenuBar* pMenuBar = m_barLeft;

    m_pMenuFile = pMenuBar->addMenu( tr("&File") );
    //m_pMenuFile->addAction( m_pActionLoadIniFile );
    //m_pMenuFile->addAction( m_pActionPrint );
    m_pMenuFile->addAction( &m_ActionExit );
    m_pMenuFile->addAction( &m_ActionConnect );

    m_pMenuSetting = pMenuBar->addMenu( tr("&Setting") );
    m_pMenuHelpL = pMenuBar->addMenu( tr("&Help") );
    //m_pMenuHelpL->addAction( &m_ActionAbout );
    //m_pMenuHelpL->addAction( &m_ActionInfo );
    m_pMenuContent = pMenuBar->addMenu( tr("Content") );

    //QMenu*          m_pMenuHelpR;
    //QMenu*          m_pMenuCreateTicket;
    pMenuBar = m_barRight;
    m_pMenuHelpR = pMenuBar->addMenu( tr("Help") );
    //m_pMenuHelpR->addAction( &m_ActionAbout );
    //m_pMenuHelpR->addAction( &m_ActionInfo );
    m_pMenuCreateTicket = pMenuBar->addMenu( tr("Create ticket") );

    ADD_ACTION_TO_MENU_HELP(&m_ActionAbout);
    ADD_ACTION_TO_MENU_HELP(&m_ActionInfo);
    ADD_ACTION_TO_MENU_HELP(&m_ActionHelp);
}


void Mainwindow_gui_wallet::InfoSlot()
{

    fc::rpc::gui* pApi = NULL;

    try
    {
        pApi = GetCurGuiApi();
        if(pApi){pApi->SetNewTask(this,TaskDoneFunc,"info");}
    }
    catch(...)
    {
        //
    }
}


void Mainwindow_gui_wallet::AboutSlot()
{
    graphene::wallet::wallet_api* pApi = NULL;
    bool bCreatedHere = false;
    std::string aStr;

    try
    {
        aStr = "";
        fc::variant_object var_obj_about;
        pApi = GetCurWalletApi();
#if 0
        if(!pApi){
            graphene::wallet::wallet_data wdata;
            get_remote_api
            pApi = new graphene::wallet::wallet_api(wdata,);
            bCreatedHere=true;
        }
#endif

        if(pApi)
        {
            var_obj_about = pApi->about();
            fc::variant_object::iterator itCur;
            fc::variant_object::iterator itBeg = var_obj_about.begin();
            fc::variant_object::iterator itEnd = var_obj_about.end();

            for(itCur=itBeg;itCur < itEnd;++itCur)
            {
                aStr += "\"";
                aStr += (*itCur).key();
                aStr += "\": \"";
                aStr += (*itCur).value().as_string();
                aStr += "\"\n";
            }

        } // if(pApi)
        else
        {
            //var_obj_about = static_about();
            aStr = "First connect to the witness node, then require again info!";
        }


    }
    catch(...)
    {
        aStr += "Exception thrown!";
    }

    m_info_dialog.setFixedSize(500,300);
    m_info_dialog->setText(tr(aStr.c_str()));
    m_info_dialog.exec();

    if(bCreatedHere){delete pApi;}
}



void Mainwindow_gui_wallet::HelpSlot()
{
    graphene::wallet::wallet_api* pApi = NULL;
    bool bCreatedHere = false;
    std::string aStr;

    try
    {
        aStr = "";
        fc::variant_object var_obj_about;
        pApi = GetCurWalletApi();

        if(pApi)
        {
            aStr = pApi->help();
        } // if(pApi)
        else
        {
            //var_obj_about = static_about();
            aStr = "First connect to the witness node, then require again info!";
        }


    }
    catch(...)
    {
        aStr += "Exception thrown!";
    }

    m_info_dialog.setMaximumSize(QSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX));
    m_info_dialog.resize(500,500);
    m_info_dialog->setText(tr(aStr.c_str()));
    m_info_dialog.exec();

    if(bCreatedHere){delete pApi;}
}


void Mainwindow_gui_wallet::TaskDoneFunc(int a_err,const std::string& a_task,const std::string& a_result)
{
    emit TaskDoneSig(a_err,a_task,a_result);
}


void Mainwindow_gui_wallet::TaskDoneFunc(void* a_owner,int a_err,const std::string& a_task,const std::string& a_result)
{
    Mainwindow_gui_wallet* pOwner = (Mainwindow_gui_wallet*)a_owner;
    pOwner->TaskDoneFunc(a_err,a_task,a_result);
}


void Mainwindow_gui_wallet::TaskDoneSlot(int a_err,std::string a_task, std::string a_result)
{
    QString aStrToDisplay(tr(a_task.c_str()));

    aStrToDisplay += tr("(err=");
    aStrToDisplay += QString::number(a_err,10);
    aStrToDisplay += tr(")\n");
    aStrToDisplay += tr(a_result.c_str());

    m_info_dialog.setFixedSize(600,500);
    m_info_dialog->setText(aStrToDisplay);
    m_info_dialog.exec();
}



void Mainwindow_gui_wallet::ConnectSlot()
{
    m_ConnectDlg.exec();
}
