/*
 *	File      : walletcontentdlg.hpp
 *
 *	Created on: 04 Jan 2017
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef WALLETCONTENTDLG_HPP
#define WALLETCONTENTDLG_HPP

#include <QDialog>
//#include <graphene/wallet/wallet.hpp>
#include "connected_api_instance.hpp"
#include <QVBoxLayout>
#include <QLabel>

#ifndef _OVERRIDE_
#if __cplusplus >= 199711L
#define _OVERRIDE_ override
#else
#define _OVERRIDE_
#endif
#endif // #ifndef _OVERRIDE_

#ifndef _LIKELY_
#define _LIKELY_(_expr_)    (_expr_)
#endif

namespace gui_wallet
{

class WalletContentDlg : public QDialog
{
    Q_OBJECT

public:
    WalletContentDlg();
    virtual ~WalletContentDlg();

    virtual int exec() _OVERRIDE_ ;

protected:
    void ListAccountThreadFunc();
    void CallShowWalletContentFunction(struct StructApi* a_pApi);

protected slots:
    void WalletContentReadySlot();

protected:
signals:
    void WalletContentReadySig();


private:
    vector<account_object>  m_vAccounts;
    vector<vector<asset>>   m_vAccountsBalances;
    QVBoxLayout             m_main_layout;
    QLabel                  m_num_acc_or_error_label;
    int                     m_nError;
    std::string             m_error_string;
};

}

#endif // WALLETCONTENTDLG_HPP
