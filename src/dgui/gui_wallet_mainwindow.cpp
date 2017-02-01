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
#include <QMoveEvent>
#include "qt_commonheader.hpp"
#include <stdio.h>
#include <stdlib.h>

#define __INFO__ 0
#define __WARN__ 1
#define __ERRR__ 2

using namespace gui_wallet;
extern int g_nDebugApplication;
static Mainwindow_gui_wallet* s_pMainWindow = NULL;

Mainwindow_gui_wallet::Mainwindow_gui_wallet()
        :
        m_ActionExit(tr("&Exit"),this),
        m_ActionConnect(tr("Connect"),this),
        m_ActionAbout(tr("About"),this),
        m_ActionInfo(tr("Info"),this),
        m_ActionHelp(tr("Help"),this),
        m_ActionWalletContent(tr("Wallet content"),this),
        m_ActionUnlock(tr("Unlock"),this),
        m_ActionImportKey(tr("Import key"),this),
        m_ActionShowDigitalContextes(tr("show dig. contexes"),this),
        m_ActionOpenCliWallet(tr("cli_wallet"),this),
        m_ActionOpenInfoDlg(tr("Open info dlg."),this),
        m_ConnectDlg(this),
        m_info_dialog(),
        m_import_key_dlg(2),
        m_cqsPreviousFilter(tr("nf"))
{
    m_pInfoTextEdit = new QTextEdit;
    if(!m_pInfoTextEdit){throw "Low memory";}
    m_pInfoTextEdit->setReadOnly(true);
    m_pcInfoDlg = new CliWalletDlg(m_pInfoTextEdit);
    if(!m_pcInfoDlg){throw "Low memory";}

    s_pMainWindow = this;
    connect(this, SIGNAL(GuiWalletInfoWarnErrSig(int,std::string)), this, SLOT(GuiWalletInfoWarnErrSlot(int,std::string)) );

    CliTextEdit* pCliTextEdit = (CliTextEdit*)m_cCliWalletDlg.operator ->();
    pCliTextEdit->SetCallbackStuff2(this,NULL,&Mainwindow_gui_wallet::CliCallbackFnc);

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

    m_nError = 0;
    m_error_string = "";

    setUnifiedTitleAndToolBarOnMac(false);

    QComboBox* pUsersCombo = &(m_pCentralWidget->usersCombo());

    connect(this, SIGNAL(TaskDoneSig(void*,int,std::string, std::string)), this, SLOT(TaskDoneSlot(void*,int,std::string, std::string)) );
    connect(this, SIGNAL(WalletContentReadySig(int)), this, SLOT(WalletContentReadySlot(int)) );
    connect(&m_ConnectDlg, SIGNAL(ConnectDoneSig()), this, SLOT(ConnectDoneSlot()) );
    //connect(pUsersCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(CurrentUserBalanceSlot(int)) );
    //void GuiWalletInfoWarnErrSlot(std::string);

    ConnectToStateChangeUpdate(this,SLOT(StateUpdateSlot(int)));

}


Mainwindow_gui_wallet::~Mainwindow_gui_wallet()
{
    disconnect(this, SIGNAL(GuiWalletInfoWarnErrSig(int,std::string)), this, SLOT(GuiWalletInfoWarnErrSlot(int,std::string)) );
    delete m_pInfoTextEdit;
    delete m_pcInfoDlg;
}


void Mainwindow_gui_wallet::CreateActions()
{
    //m_pActionLoadIniFile = new QAction( tr("&Load ini"), this );
    //m_pActionLoadIniFile->setIcon( QIcon(":/images/open.png") );
    //m_pActionLoadIniFile->setShortcut( QKeySequence::Open );
    //m_pActionLoadIniFile->setStatusTip( tr("Load ini file") );
    //connect( m_pActionLoadIniFile, SIGNAL(triggered()), this, SLOT(LoadIniFileSlot()) );

    /**************************************************************************/

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

    m_ActionWalletContent.setDisabled(true);
    m_ActionWalletContent.setStatusTip( tr("Wallet content") );
    connect( &m_ActionWalletContent, SIGNAL(triggered()), this, SLOT(ShowWalletContentSlot()) );

    m_ActionUnlock.setDisabled(true);
    m_ActionUnlock.setStatusTip( tr("Unlock account") );
    connect( &m_ActionUnlock, SIGNAL(triggered()), this, SLOT(UnlockSlot()) );

    m_ActionImportKey.setDisabled(true);
    m_ActionImportKey.setStatusTip( tr("Import key") );
    connect( &m_ActionImportKey, SIGNAL(triggered()), this, SLOT(ImportKeySlot()) );

    //m_ActionShowDigitalContextes
    connect( &m_ActionShowDigitalContextes, SIGNAL(triggered()), this, SLOT(ShowDigitalContextesSlot()) );

    m_ActionOpenCliWallet.setStatusTip( tr("Open CLI wallet dialog") );
    connect( &m_ActionOpenCliWallet, SIGNAL(triggered()), this, SLOT(OpenCliWalletDlgSlot()) );

    m_ActionOpenInfoDlg.setStatusTip( tr("Open Info dialog") );
    connect( &m_ActionOpenInfoDlg, SIGNAL(triggered()), this, SLOT(OpenInfoDlgSlot()) );

}


void Mainwindow_gui_wallet::CreateMenues()
{
#define ADD_ACTION_TO_MENU_HELP(__action_ptr__) \
    do{m_pMenuHelpL->addAction( (__action_ptr__) );m_pMenuHelpR->addAction( (__action_ptr__) );}while(0)

    QMenuBar* pMenuBar = m_barLeft;

    m_pMenuFile = pMenuBar->addMenu( tr("&File") );
    m_pMenuFile->addAction( &m_ActionExit );
    m_pMenuFile->addAction( &m_ActionConnect );
    m_pMenuFile->addAction( &m_ActionUnlock );
    m_pMenuFile->addAction( &m_ActionImportKey );

    m_pMenuSetting = pMenuBar->addMenu( tr("&Setting") );
    m_pMenuHelpL = pMenuBar->addMenu( tr("&Help") );

    m_pMenuContent = pMenuBar->addMenu( tr("Content") );
    m_pMenuContent->addAction( &m_ActionWalletContent );

    m_pMenuDebug = pMenuBar->addMenu( tr("Debug") );
    m_pMenuDebug->addAction(&m_ActionOpenCliWallet);
    m_pMenuDebug->addAction(&m_ActionOpenInfoDlg);
    m_pMenuTempFunctions = m_pMenuDebug->addMenu(tr("temp. functions start"));
    m_pMenuTempFunctions->addAction(&m_ActionShowDigitalContextes);

    /******************************************************/
    pMenuBar = m_barRight;
    m_pMenuHelpR = pMenuBar->addMenu( tr("Help") );

    m_pMenuCreateTicket = pMenuBar->addMenu( tr("Create ticket") );

    /******************************************************/
    ADD_ACTION_TO_MENU_HELP(&m_ActionAbout);
    ADD_ACTION_TO_MENU_HELP(&m_ActionInfo);
    ADD_ACTION_TO_MENU_HELP(&m_ActionHelp);
}


void Mainwindow_gui_wallet::StateUpdateSlot(int a_state)
{
    switch(a_state)
    {
    case UNLOCKED_ST:
    {
        QString cqsNewFilter = m_pCentralWidget->getFilterText();

        if(cqsNewFilter==m_cqsPreviousFilter){return;}

        else if(cqsNewFilter==tr(""))
        {
            // may be in the case of no fiolter all contents should be displayed?
            m_cqsPreviousFilter = cqsNewFilter;
            return;
        }

        m_cqsPreviousFilter = cqsNewFilter;
        ShowDigitalContextesSlot(cqsNewFilter);

        break;
    }
    default:
        break;
    }
}


int GuiWalletInfoWarnErrGlobal(int a_nType,const char* a_form, ...)
{
    va_list aArgs ;
    va_start(aArgs,a_form);
    int nReturn = s_pMainWindow->GuiWalletInfoWarnErr(a_nType,a_form,aArgs);
    va_end (aArgs);
    return nReturn;
}


int Mainwindow_gui_wallet::GuiWalletInfoStatic(void* a_owner,const char* a_form, ...)
{
    va_list aArgs ;
    va_start(aArgs,a_form);
    int nReturn = ((Mainwindow_gui_wallet*)a_owner)->GuiWalletInfoWarnErr(__INFO__,a_form,aArgs);
    va_end (aArgs);
    return nReturn;
}


int Mainwindow_gui_wallet::GuiWalletWarnStatic(void* a_owner,const char* a_form, ...)
{
    va_list aArgs ;
    va_start(aArgs,a_form);
    int nReturn = ((Mainwindow_gui_wallet*)a_owner)->GuiWalletInfoWarnErr(__WARN__,a_form,aArgs);
    va_end (aArgs);
    return nReturn;
}


int Mainwindow_gui_wallet::GuiWalletErrrStatic(void* a_owner,const char* a_form, ...)
{
    va_list aArgs ;
    va_start(aArgs,a_form);
    int nReturn = ((Mainwindow_gui_wallet*)a_owner)->GuiWalletInfoWarnErr(__ERRR__,a_form,aArgs);
    va_end (aArgs);
    return nReturn;
}


int Mainwindow_gui_wallet::GuiWalletInfoWarnErr(int a_nType,const char* a_form, va_list a_args)
{
    char* pcBuffer(NULL);
    int nReturn (0), nFreeBuffer;
    if(g_nDebugApplication){vprintf(a_form,a_args);}

#ifdef WIN32
//#if 1
    int nBuffSize(0);
    char *pcTemp;

    do{
        nBuffSize += 1024;
        pcTemp =  (char*)realloc(pcBuffer,nBuffSize);
        if(!pcTemp){free(pcBuffer);return 0;}
        pcBuffer = pcTemp;
        nReturn = _vsnprintf(pcBuffer,nBuffSize,a_form,a_args);
    }while(nReturn<0);

    nFreeBuffer = 1;

#else  // #ifdef WIN32
    nReturn = vsnprintf(NULL,0,a_form,a_args);

    if(nReturn<4095) // There will not be stack overflow
    {
        pcBuffer = (char*)alloca(nReturn+2);
        nFreeBuffer = 0;
    }
    else
    {
        pcBuffer = (char*)malloc(nReturn + 2);
        nFreeBuffer = 1;
    }

    nReturn = vsnprintf(pcBuffer,nReturn+1,a_form,a_args);
    std::string csTextToHandle(pcBuffer);
    emit GuiWalletInfoWarnErrSig(a_nType,csTextToHandle);

#endif // #ifdef WIN32

    if(nFreeBuffer)
    {
        free(pcBuffer);
    }

    return nReturn;
}

void Mainwindow_gui_wallet::GuiWalletInfoWarnErrSlot(int a_type,std::string a_csTextToHandle)
{
    switch(a_type)
    {
    case __WARN__:
        (*m_pcInfoDlg)->setTextColor(Qt::darkYellow);
        break;
    case __ERRR__:
        (*m_pcInfoDlg)->setTextColor(Qt::red);
        break;
    default:
        (*m_pcInfoDlg)->setTextColor(Qt::black);
        break;
    }

    m_pcInfoDlg->appentText(a_csTextToHandle);
}


void Mainwindow_gui_wallet::CliCallbackFunction(struct StructApi* a_pApi)
{
    if(a_pApi && a_pApi->gui_api)
    {
        (a_pApi->gui_api)->SetNewTask(this,(void*)-1,m_cli_line,&Mainwindow_gui_wallet::TaskDoneFunc);
    }
    else
    {
        m_cCliWalletDlg->setTextColor(Qt::red);
        m_cCliWalletDlg.appentText("first connect the wallet to the witness node!");
        m_cCliWalletDlg->setTextColor(Qt::black);
        m_cCliWalletDlg.appentText(">>>");
    }
}


void Mainwindow_gui_wallet::CliCallbackFnc(void*/*arg*/,const std::string& a_task)
{
    m_cli_line = a_task;
    UseConnectedApiInstance(this,&Mainwindow_gui_wallet::CliCallbackFunction);
}


void Mainwindow_gui_wallet::OpenCliWalletDlgSlot()
{
    m_cCliWalletDlg.exec();
}


void Mainwindow_gui_wallet::OpenInfoDlgSlot()
{
    m_pcInfoDlg->exec();
}


void Mainwindow_gui_wallet::CurrentUserBalanceSlot(int a_nIndex)
{
    if(a_nIndex>=0){UseConnectedApiInstance(this,&Mainwindow_gui_wallet::CurrentUserBalanceFunction);}
}


void Mainwindow_gui_wallet::CurrentUserBalanceFunction(struct StructApi* a_pApi)
{
    int nCurUserIndex ( m_pCentralWidget->usersCombo().currentIndex() );
    const int cnSize ( m_pCentralWidget->usersCombo().count() );
    if((nCurUserIndex>=0) && cnSize)
    {

        m_vAccountsBalances.resize(cnSize);
        QString cqsUserName = m_pCentralWidget->usersCombo().currentText();
        QByteArray cLatin = cqsUserName.toLatin1();
        std::string csAccName = cLatin.data();

        __ulli64 ullnCurUserAndUpdate = (((__ulli64)nCurUserIndex)<<32 ) | 1;

        std::string csTaskString = "list_account_balances " + csAccName;
        if(a_pApi && a_pApi->gui_api){(a_pApi->gui_api)->SetNewTask(
                        this,(void*)ullnCurUserAndUpdate,csTaskString,&Mainwindow_gui_wallet::TaskDoneFunc);}
    }
}


void Mainwindow_gui_wallet::ShowDigitalContextesSlot(QString a_filter)
{
    m_cqsCurrentFilter = a_filter;
    UseConnectedApiInstance(this,&Mainwindow_gui_wallet::ShowDigitalContextesFunction);
}


void Mainwindow_gui_wallet::ShowDigitalContextesFunction(struct StructApi* a_pApi)
{
    QString& cqsFilter = m_cqsCurrentFilter;

#ifdef WALLET_API_DIRECT_CALLS
    if(a_pApi && a_pApi->wal_api)
    {
        optional<content_object> cContent;
        std::vector<content_object> cvContents = a_pApi->wal_api->list_content("a",5);

        const int nSize = cvContents.size();
        if(g_nDebugApplication){printf("Number of digital contents = %d\n",nSize);}
        for(int i(0); i<nSize;++i)
        {
            if(g_nDebugApplication){printf("%d, uri=\"%s\"\n",i,cvContents[i].URI.c_str());}
            cContent = a_pApi->wal_api->get_content(cvContents[i].URI);
            if(g_nDebugApplication){printf("valid=%d\n",(int)cContent.valid());}
        }

    }
#else  // #ifdef WALLET_API_DIRECT_CALLS

    if(a_pApi && a_pApi->gui_api)
    {
        QByteArray cqbaFilter = cqsFilter.toLatin1();
        std::string csTaskLine = std::string("list_content") + cqbaFilter.data() + "10";

        a_pApi->gui_api->SetNewTask(this,NULL,csTaskLine,&Mainwindow_gui_wallet::TaskDoneFunc);
    }

#endif  // #ifdef WALLET_API_DIRECT_CALLS
}


void Mainwindow_gui_wallet::ConnectDoneSlot()
{
    WalletContentReadySlot(0);
    m_ActionWalletContent.setEnabled(true);
    m_ActionUnlock.setEnabled(true);
    m_ActionImportKey.setEnabled(true);
}


void Mainwindow_gui_wallet::UnlockSlot()
{
    UseConnectedApiInstance(this,&Mainwindow_gui_wallet::UnlockFunction);
    //wapiptr->unlock(aPassword);
}


void Mainwindow_gui_wallet::UnlockFunction(struct StructApi* a_pApi)
{
    graphene::wallet::wallet_api* pWapi = a_pApi ? a_pApi->wal_api : NULL;

    try
    {
        if(pWapi)
        {
            QPoint thisPos = pos();
            std::vector<std::string> cvsPassword(1);
            decent::gui::tools::RET_TYPE rtRet = m_PasswdDialog2.execRD(&thisPos,cvsPassword);
            if(rtRet == decent::gui::tools::RDB_OK){pWapi->unlock(cvsPassword[0]);}
        } // if(pWapi)
    }
    catch(const fc::exception& a_fc)
    {
        if(g_nDebugApplication){printf("file:\"" __FILE__ "\",line:%d\n",__LINE__);}
        m_nError = 1;
        m_error_string = a_fc.to_detail_string();
        if(g_nDebugApplication){printf("%s\n",(a_fc.to_detail_string()).c_str());}
    }
    catch(...)
    {
        if(g_nDebugApplication){printf("file:\"" __FILE__ "\",line:%d\n",__LINE__);}
        m_nError = 2;
        m_error_string = "Unknown exception!";
        if(g_nDebugApplication){printf("Unknown exception\n");}
    }

}


void Mainwindow_gui_wallet::moveEvent(QMoveEvent * a_event)
{
    //m_wallet_content_dlg.move( mapToGlobal(a_event->pos()));
    m_wallet_content_dlg.move( /*mapToGlobal*/(a_event->pos()));
}


void Mainwindow_gui_wallet::ListAccountThreadFunc(int a_nDetailed)
{
    UseConnectedApiInstance(this,&Mainwindow_gui_wallet::CallShowWalletContentFunction);
    emit WalletContentReadySig(a_nDetailed);
}


void Mainwindow_gui_wallet::WalletContentReadySlot(int a_nDetailed)
{
    if(_LIKELY_(!m_nError))
    {
        std::string csBalanceName;
        asset* pAccountBalance;
        account_object* pAccount;
        QComboBox& cAccountsCombo = m_pCentralWidget->usersCombo();
        int nCount = cAccountsCombo.count();
        const int cnNumOfAccounts(m_vAccounts.size());
        int j,nNumbOfBalances;

        while(nCount>0){cAccountsCombo.removeItem(0);--nCount;}

        for(int i(0); i<cnNumOfAccounts;++i)
        {
            pAccount = &m_vAccounts[i];
            cAccountsCombo.addItem(tr(pAccount->name.c_str()));
            nNumbOfBalances = m_vAccountsBalances[i].size();
            for(j=0;j<nNumbOfBalances;++j)
            {
                //
            }

            if(g_nDebugApplication){printf("nNumbOfBalances=%d\n",nNumbOfBalances);}
            if(nNumbOfBalances>0)
            {
                int nIndexOfuser = m_pCentralWidget->usersCombo().currentIndex();
                pAccountBalance = &((m_vAccountsBalances[i])[nIndexOfuser>0 ? nIndexOfuser : 0]);
                //csBalanceName = (std::string)pAccountBalance->asset_id;
                csBalanceName = "DECENT";
                m_pCentralWidget->SetAccountBalanceGUI( pAccountBalance->amount.value,csBalanceName);
            }
        }
    }

    if(a_nDetailed){m_wallet_content_dlg.execWCt(m_vAccounts,m_vAccountsBalances,m_nError,m_error_string);}

}


void Mainwindow_gui_wallet::CallShowWalletContentFunction(struct StructApi* a_pApi)
{
    graphene::wallet::wallet_api* pWapi = a_pApi ? a_pApi->wal_api : NULL;

    try
    {
        if(pWapi)
        {
            account_object* pAcc;
            m_vAccounts = pWapi->list_my_accounts();
            const int cnNumOfAccounts(m_vAccounts.size());
            //m_vAccountsBalances.reserve(cnNumOfAccounts);
            m_vAccountsBalances.resize(cnNumOfAccounts);
            for(int i(0); i<cnNumOfAccounts;++i)
            {
                pAcc = &(m_vAccounts[i]);
#ifdef LIST_ACCOUNT_BALANCES_DIRECT_CALL
                m_vAccountsBalances[i] = pWapi->list_account_balances(((std::string)(pAcc->id)));
#else
                m_vAccountsBalances[i].clear();
                if(a_pApi->gui_api)
                {
                    int nUpdate = (i==(cnNumOfAccounts-1)) ? 1 : 0;
                    __ulli64 ullnAccountAndUpdate = ((__ulli64)i)<<32 | nUpdate;
                    std::string csTaskString = "list_account_balances " + ((std::string)(pAcc->id));
                    (a_pApi->gui_api)->SetNewTask(this,(void*)ullnAccountAndUpdate,csTaskString,&Mainwindow_gui_wallet::TaskDoneFunc);
                }
#endif
            }
        }
    }
    catch(const fc::exception& a_fc)
    {
        if(g_nDebugApplication){printf("file:\"" __FILE__ "\",line:%d\n",__LINE__);}
        m_nError = 1;
        m_error_string = a_fc.to_detail_string();
        if(g_nDebugApplication){printf("%s\n",(a_fc.to_detail_string()).c_str());}
    }
    catch(...)
    {
        if(g_nDebugApplication){printf("file:\"" __FILE__ "\",line:%d\n",__LINE__);}
        m_nError = 2;
        m_error_string = "Unknown exception!";
        if(g_nDebugApplication){printf("Unknown exception\n");}
    }

}


void Mainwindow_gui_wallet::ImportKeySlot()
{
    m_nError = 0;
    m_error_string = "";
    UseConnectedApiInstance(this,&Mainwindow_gui_wallet::CallImportKeyFunction);
}


void Mainwindow_gui_wallet::ShowWalletContentSlot()
{
    //m_wallet_content_dlg.exec();

    m_nError = 0;
    m_error_string = "";
    std::thread aListAccountThread(&Mainwindow_gui_wallet::ListAccountThreadFunc,this,1);
    aListAccountThread.detach();
}


void Mainwindow_gui_wallet::CallInfoFunction(struct StructApi* a_pApi)
{
    try
    {
        if(a_pApi && (a_pApi->gui_api)){(a_pApi->gui_api)->SetNewTask(this,NULL,"info",&Mainwindow_gui_wallet::TaskDoneFunc);}
    }
    catch(const fc::exception& a_fc)
    {
        if(g_nDebugApplication){printf("file:\"" __FILE__ "\",line:%d\n",__LINE__);}
        //(*a_fpErr)(a_pOwner,a_fc.to_string(),a_fc.to_detail_string());
        if(g_nDebugApplication){printf("%s\n",(a_fc.to_detail_string()).c_str());}
    }
    catch(...)
    {
        if(g_nDebugApplication){printf("file:\"" __FILE__ "\",line:%d\n",__LINE__);}
        if(g_nDebugApplication){printf("Unknown exception\n");}
    }
}


void Mainwindow_gui_wallet::CallImportKeyFunction(struct StructApi* a_pApi)
{
    try
    {
        if(a_pApi && (a_pApi->wal_api))
        {
            //QByteArray cLatin;
            std::vector<std::string> cvsUsKey(2);
            //QString cqsUserName(tr("nathan"));
            //QString cqsKey(tr("5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3"));
            //std::string csUser_name, csKey;
            QComboBox& cUsersCombo = m_pCentralWidget->GetUsersList();

            cvsUsKey[0] = "nathan";
            cvsUsKey[1] = "5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3";

            if(cUsersCombo.count())
            {
                QString cqsUserName = cUsersCombo.currentText();
                QByteArray cbaResult = cqsUserName.toLatin1();
                cvsUsKey[0] = cbaResult.data();
            }

            QPoint thisPos = pos();
            decent::gui::tools::RET_TYPE aRet = m_import_key_dlg.execRD(&thisPos,cvsUsKey);
            if(aRet == decent::gui::tools::RDB_CANCEL){return ;}
            //cLatin = cqsUserName.toLatin1();
            //csUser_name = cLatin.data();
            //cLatin = cqsKey.toLatin1();
            //csKey = cLatin.data();
#ifdef WALLET_API_DIRECT_CALLS
            (a_pApi->wal_api)->import_key(cvsUsKey[0],cvsUsKey[1]);
#else  // #ifdef WALLET_API_DIRECT_CALLS
            if(a_pApi->gui_api)
            {
                std::string csTaskStr = "import_key " + cvsUsKey[0] + " " + cvsUsKey[1];
                if(g_nDebugApplication){printf("!!!task: %s\n",csTaskStr.c_str());}
                (a_pApi->gui_api)->SetNewTask(this,NULL,csTaskStr,&Mainwindow_gui_wallet::TaskDoneFunc);
            }
#endif  // #ifdef WALLET_API_DIRECT_CALLS

        } // if(a_pApi && (a_pApi->wal_api))
    } // try
    catch(const fc::exception& a_fc)
    {
        //(*a_fpErr)(a_pOwner,a_fc.to_string(),a_fc.to_detail_string());
        if(g_nDebugApplication){printf("%s\n",(a_fc.to_detail_string()).c_str());}
    }
    catch(...)
    {
        if(g_nDebugApplication){printf("Unknown exception\n");}
    }

    emit WalletContentReadySig(0);
}


void Mainwindow_gui_wallet::InfoSlot()
{
    UseConnectedApiInstance<Mainwindow_gui_wallet>(this,&Mainwindow_gui_wallet::CallInfoFunction);
}


void Mainwindow_gui_wallet::CallAboutFunction(struct StructApi* a_pApi)
{
    graphene::wallet::wallet_api* pApi = NULL;
    bool bCreatedHere = false;
    std::string aStr;

    try
    {
        aStr = "";
        fc::variant_object var_obj_about;
        pApi = a_pApi ? a_pApi->wal_api : NULL;
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
    catch(const fc::exception& a_fc)
    {
        aStr += a_fc.to_detail_string();
        //(*a_fpErr)(a_pOwner,a_fc.to_string(),a_fc.to_detail_string());
        if(g_nDebugApplication){printf("%s\n",(a_fc.to_detail_string()).c_str());}
    }
    catch(...)
    {
        aStr += "Unknown Exception thrown!";
        if(g_nDebugApplication){printf("Unknown exception\n");}
    }

    m_info_dialog.setFixedSize(500,300);
    m_info_dialog->setText(tr(aStr.c_str()));
    m_info_dialog.exec();

    if(bCreatedHere){delete pApi;}

}

void Mainwindow_gui_wallet::AboutSlot()
{
    UseConnectedApiInstance<Mainwindow_gui_wallet>(this,&Mainwindow_gui_wallet::CallAboutFunction);
}


void Mainwindow_gui_wallet::CallHelpFunction(struct StructApi* a_pApi)
{
    graphene::wallet::wallet_api* pApi = NULL;
    bool bCreatedHere = false;
    std::string aStr;

    try
    {
        aStr = "";
        //fc::variant_object var_obj_about;
        pApi = a_pApi ? a_pApi->wal_api : NULL;

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
    catch(const fc::exception& a_fc)
    {
        aStr += a_fc.to_detail_string();
        //(*a_fpErr)(a_pOwner,a_fc.to_string(),a_fc.to_detail_string());
        if(g_nDebugApplication){printf("%s\n",(a_fc.to_detail_string()).c_str());}
    }
    catch(...)
    {
        aStr += "Unknown Exception thrown!";
        if(g_nDebugApplication){printf("Unknown exception\n");}
    }

    m_info_dialog.setMaximumSize(QSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX));
    m_info_dialog.resize(500,500);
    m_info_dialog->setText(tr(aStr.c_str()));
    m_info_dialog.exec();

    if(bCreatedHere){delete pApi;}
}

void Mainwindow_gui_wallet::HelpSlot()
{
    UseConnectedApiInstance<Mainwindow_gui_wallet>(this,&Mainwindow_gui_wallet::CallHelpFunction);
}


void Mainwindow_gui_wallet::TaskDoneFunc(void* a_callbackArg,int a_err,const std::string& a_task,const std::string& a_result)
{
    emit TaskDoneSig(a_callbackArg,a_err,a_task,a_result);
}


void Mainwindow_gui_wallet::ConnectSlot()
{
    m_nError = 0;
    m_error_string = "";
    m_ConnectDlg.exec();
    UseConnectedApiInstance(this,&Mainwindow_gui_wallet::SetupInfoWarnErrrFunctions);
}


void Mainwindow_gui_wallet::SetupInfoWarnErrrFunctions(struct StructApi* a_pApi)
{
    if(a_pApi && a_pApi->gui_api)
    {
        (a_pApi->gui_api)->SetOwner(this);
        (a_pApi->gui_api)->SetInfoReporter(&GuiWalletInfoStatic);
        (a_pApi->gui_api)->SetWarnReporter(&GuiWalletWarnStatic);
        (a_pApi->gui_api)->SetErrorReporter(&GuiWalletErrrStatic);
    }
    else
    {
        GuiWalletInfoWarnErrSlot(__ERRR__,"Connection not sucessfull");
    }
}


void Mainwindow_gui_wallet::TaskDoneSlot(void* a_arg,int a_err,std::string a_task, std::string a_result)
{

    if(g_nDebugApplication){printf("fnc:%s, arg=%p, task=%s, result=%s\n",__FUNCTION__,a_arg,a_task.c_str(),a_result.c_str());}

    if(a_arg == ((void*)-1))
    {
        if(a_err)
        {
            m_cCliWalletDlg->setTextColor(Qt::red);
        }
    }

    if( strstr(a_task.c_str(),"info"))
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
    else if(strstr(a_task.c_str(),"list_account_balances"))
    {
        int nCurUserIndex, nUpdate;

        if(a_arg == ((void*)-1))
        {
            goto donePoint;
            if(g_nDebugApplication){printf("line:%d\n",__LINE__);}
            QComboBox& aCombo = m_pCentralWidget->usersCombo() ;
            if(g_nDebugApplication){printf("line:%d\n",__LINE__);}
            nCurUserIndex = aCombo.currentIndex();
            if(g_nDebugApplication){printf("line:%d\n",__LINE__);}
            nUpdate = 1;
            if(g_nDebugApplication){printf("line:%d\n",__LINE__);}
        }
        else
        {
            __ulli64 ullnUserAndUpdate = (__ulli64)a_arg;
            nCurUserIndex = (int)((ullnUserAndUpdate>>32) & 0xffffffff);
            nUpdate = (int)(ullnUserAndUpdate & 0xffffffff);
        }

        if(g_nDebugApplication){printf("cur_index=%d\n",nCurUserIndex);}
        if(nCurUserIndex<0){return;}

        if((((int)m_vAccountsBalances.size()) -1) < nCurUserIndex)
        {
            m_vAccountsBalances.resize(nCurUserIndex+1);
        }

        if(g_nDebugApplication){printf("line:%d\n",__LINE__);}
        double lfDecents = strtod(a_result.c_str(),NULL);
        if(g_nDebugApplication){printf("line:%d\n",__LINE__);}
        std::vector<asset> vAssets;
        if(g_nDebugApplication){printf("line:%d\n",__LINE__);}

        if(lfDecents>0){vAssets.push_back(asset(lfDecents)); m_vAccountsBalances[nCurUserIndex]=vAssets;}
        if(g_nDebugApplication){printf("line:%d\n",__LINE__);}

        if(g_nDebugApplication){printf("lfDecents=%lf, nCurUserIndex=%d, string=\"%s\"\n", lfDecents,nCurUserIndex,a_result.c_str());}
        if(g_nDebugApplication){printf("line:%d\n",__LINE__);}

        if(g_nDebugApplication){printf("nCurUserIndex=%d, nUpdate=%d\n",nCurUserIndex,nUpdate);}
        if(g_nDebugApplication){printf("line:%d\n",__LINE__);}
        if(nUpdate){emit WalletContentReadySig(0);}
        if(g_nDebugApplication){printf("line:%d\n",__LINE__);}
    }
    else if(strstr(a_task.c_str(),"list_content "))
    {
        QTableWidget& cContents = m_pCentralWidget->getDigitalContentsTable();
    }
    else if(strstr(a_task.c_str(),"get_content "))
    {
        //
    }
    else if(strstr(a_task.c_str(),"info"))
    {
        //
    }
    else if(strstr(a_task.c_str(),"import_key "))
    {
        std::thread aListAccountThread(&Mainwindow_gui_wallet::ListAccountThreadFunc,this,0);
        aListAccountThread.detach();
    }

donePoint:
    if(a_arg == ((void*)-1))
    {
        m_cCliWalletDlg.appentText(a_result);
        if(a_err){ m_cCliWalletDlg->setTextColor(Qt::black);}
        m_cCliWalletDlg.appentText(">>>");
    }

}
