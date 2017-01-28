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
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "gui_wallet_connectdlg.hpp"
#include "text_display_dialog.hpp"
#include "walletcontentdlg.hpp"
#include "richdialog.hpp"
#include "cliwalletdlg.hpp"
#include <unnamedsemaphorelite.hpp>

namespace gui_wallet
{

    //class Mainwindow_gui_wallet : public QMainWindow
    class Mainwindow_gui_wallet : public QMainWindow
    {
        Q_OBJECT
    public:
        Mainwindow_gui_wallet();
        virtual ~Mainwindow_gui_wallet();   // virtual because may be this class will be
                                            // used by inheritance
        void CreateActions();
        void CreateMenues();

#ifndef LIST_ACCOUNT_BALANCES_DIRECT_CALL
        void __EmitWalletcontentReadyFnc(int det);
#endif

    private:
        void TaskDoneFunc(void* clbkArg,int err,const std::string& task,const std::string& result);

    private:
        void CallInfoFunction(struct StructApi* pApi);
        void CallAboutFunction(struct StructApi* a_pApi);
        void CallHelpFunction(struct StructApi* a_pApi);
        void CallImportKeyFunction(struct StructApi* a_pApi);
        void CallShowWalletContentFunction(struct StructApi* a_pApi);
        void UnlockFunction(struct StructApi* a_pApi);
        void ShowDigitalContextesFunction(struct StructApi* a_pApi);

        void ListAccountThreadFunc(int a_nDetailed);

        void CurrentUserBalanceFunction(struct StructApi* a_pApi);

        void CliCallbackFunction(struct StructApi* a_pApi);

    private:
        void CliCallbackFnc(void*arg,const std::string& task);

    protected slots:/* Instead of these one line slots
                     *, probably should be used lambda functions?
                     * Is it possible to do?
                     */
        void AboutSlot();
        void HelpSlot();
        void InfoSlot();

        void ShowWalletContentSlot();
        void WalletContentReadySlot(int a_nDetailed);
        void CurrentUserBalanceSlot(int index );

    protected slots:
        void ConnectSlot();
        void ImportKeySlot();
        void UnlockSlot();
        void TaskDoneSlot(void*arg,int err,std::string task, std::string result);
        void ConnectDoneSlot();
        void ShowDigitalContextesSlot();
        void OpenCliWalletDlgSlot();

    private:
    signals:
        void TaskDoneSig(void* clbkArg,int err,std::string task, std::string result);
        void WalletContentReadySig(int a_nDetailed);

    protected:
        virtual void moveEvent(QMoveEvent *) _OVERRIDE_ ;

    private:
        class QVBoxLayout*   m_pCentralAllLayout;
        class QHBoxLayout*   m_pMenuLayout;
        CentralWigdet*       m_pCentralWidget;

        QMenuBar *          m_barLeft ;
        QMenuBar *          m_barRight;
        QMenu*              m_pMenuFile;
        QMenu*              m_pMenuSetting;
        QMenu*              m_pMenuHelpL;
        QMenu*              m_pMenuContent;
        QMenu*              m_pMenuHelpR;
        QMenu*              m_pMenuCreateTicket;
        QMenu*              m_pMenuDebug;
        QMenu*              m_pMenuTempFunctions;
        QAction             m_ActionExit;
        QAction             m_ActionConnect;
        QAction             m_ActionAbout;
        QAction             m_ActionInfo;
        QAction             m_ActionHelp;
        QAction             m_ActionWalletContent;
        QAction             m_ActionUnlock;
        QAction             m_ActionImportKey;
        QAction             m_ActionShowDigitalContextes;
        QAction             m_ActionOpenCliWallet;
        ConnectDlg          m_ConnectDlg;
        TextDisplayDialog   m_info_dialog;
        WalletContentDlg    m_wallet_content_dlg;

        vector<account_object>  m_vAccounts;
    public:
        vector<vector<asset>>   m_vAccountsBalances;
    private:
        QVBoxLayout             m_main_layout;
        QLabel                  m_num_acc_or_error_label;
        int                     m_nError;
        std::string             m_error_string;
        PasswordDialog          m_PasswdDialog2;

    private:
        /*class ImportKeyDialog : private QDialog
        {
        public:
            ImportKeyDialog():m_us_name_lab(tr("Username")),m_pub_key_lab(tr("private_wif_key")){
                m_us_name_lay.addWidget(&m_us_name_lab); m_us_name_lay.addWidget(&m_user_name);
                m_pub_key_lay.addWidget(&m_pub_key_lab); m_pub_key_lay.addWidget(&m_pub_key);
                m_layout.addLayout(&m_us_name_lay);m_layout.addLayout(&m_pub_key_lay);
                setLayout(&m_layout);
            }

            void exec(const QPoint& a_move,QString& a_us_nm, QString& a_pub_k)
            {
                m_user_name.setText(a_us_nm);m_pub_key.setText(a_pub_k);
                QDialog::move(a_move); QDialog::exec();
                a_us_nm = m_user_name.text();a_pub_k=m_pub_key.text();
            }
            QHBoxLayout m_layout;
            QVBoxLayout m_us_name_lay, m_pub_key_lay;
            QLabel m_us_name_lab,m_pub_key_lab;
            QLineEdit m_user_name, m_pub_key;
        }m_import_key_dlg;*/
        decent::gui::tools::RichDialog m_import_key_dlg;

    private:
        CliWalletDlg                        m_cCliWalletDlg;
        std::string                         m_cli_line;
    };

}

#endif // MAINWINDOW_GUI_WALLET_H
