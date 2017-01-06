/*
 *	File      : walletcontentdlg.cpp
 *
 *	Created on: 04 Jan 2017
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */

#include "walletcontentdlg.hpp"
#include <thread>
#include <iostream>

extern int g_nDebugApplication;

gui_wallet::WalletContentDlg::WalletContentDlg()
{
    m_main_layout.addWidget(&m_num_acc_or_error_label);
    setLayout(&m_main_layout);
    connect(this, SIGNAL(WalletContentReadySig()), this, SLOT(WalletContentReadySlot()) );
}

gui_wallet::WalletContentDlg::~WalletContentDlg()
{
}


int gui_wallet::WalletContentDlg::exec()
{
    m_nError = 0;
    m_error_string = "";
    std::thread aListAccountThread(&gui_wallet::WalletContentDlg::ListAccountThreadFunc,this);
    aListAccountThread.detach();

    return QDialog::exec();
}


void gui_wallet::WalletContentDlg::ListAccountThreadFunc()
{
    UseConnectedApiInstance(this,&gui_wallet::WalletContentDlg::CallShowWalletContentFunction);
    emit WalletContentReadySig();
}


static void acount_balance_done_fnc(void*/*owner*/,int /*err*/,const std::string& /*a_task*/, const std::string& a_task_result)
{
    if(g_nDebugApplication){printf("%s\n", a_task_result.c_str());}
}


void gui_wallet::WalletContentDlg::CallShowWalletContentFunction(struct StructApi* a_pApi)
{
    graphene::wallet::wallet_api* pWapi = a_pApi ? a_pApi->wal_api : NULL;

    try
    {
        if(pWapi)
        {
            account_object* pAcc;
            m_vAccounts = pWapi->list_my_accounts();
            const int cnNumOfAccounts(m_vAccounts.size());
            m_vAccountsBalances.reserve(cnNumOfAccounts);
            for(int i(0); i<cnNumOfAccounts;++i)
            {
                pAcc = &(m_vAccounts[i]);
#if 0
                m_vAccountsBalances[i] = pWapi->list_account_balances(((std::string)(pAcc->id)));
#else
                if(a_pApi->gui_api)
                {
                    std::string csTaskString = "list_account_balances " + ((std::string)(pAcc->id));
                    (a_pApi->gui_api)->SetNewTask(this,acount_balance_done_fnc,csTaskString);
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

    emit WalletContentReadySig();
}


void gui_wallet::WalletContentDlg::WalletContentReadySlot()
{
    // To be done

    if(_LIKELY_(!m_nError))
    {
        const int cnNumOfAccounts(m_vAccounts.size());
        QString aNumOfAccStr = tr("Number of accounts: ") + QString::number(cnNumOfAccounts,10);
        m_num_acc_or_error_label.setText(aNumOfAccStr);
    }
    else
    {
        QString aNumOfAccStr = tr("Error accured: \n") + tr(m_error_string.c_str());
        m_num_acc_or_error_label.setText(aNumOfAccStr);
    }

    //QString a
}
