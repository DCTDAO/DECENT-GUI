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
#include "gui_wallet_connectdlg.hpp"
#include "text_display_dialog.hpp"
#include "walletcontentdlg.hpp"

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

    private:
        void TaskDoneFunc(int err,const std::string& task,const std::string& result);
        static void TaskDoneFunc(void* owner,int err,const std::string& task,const std::string& result);

    private:
        void CallInfoFunction(struct StructApi* pApi);
        void CallAboutFunction(struct StructApi* a_pApi);
        void CallHelpFunction(struct StructApi* a_pApi);

    protected slots:/* Instead of these one line slots
                     *, probably should be used lambda functions?
                     * Is it possible to do?
                     */
        void AboutSlot();
        void HelpSlot();
        void InfoSlot();

        void ShowWalletContentSlot();

    protected slots:
        void ConnectSlot();
        void TaskDoneSlot(int err,std::string task, std::string result);

    private:
    signals:
        void TaskDoneSig(int err,std::string task, std::string result);

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
        QAction             m_ActionExit;
        QAction             m_ActionConnect;
        QAction             m_ActionAbout;
        QAction             m_ActionInfo;
        QAction             m_ActionHelp;
        QAction             m_ActionWalletContent;
        ConnectDlg          m_ConnectDlg;
        TextDisplayDialog   m_info_dialog;
        WalletContentDlg    m_wallet_content_dlg;
    };

}

#endif // MAINWINDOW_GUI_WALLET_H
