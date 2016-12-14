/*
 *	File: gui_wallet_connectdlg.hpp
 *
 *	Created on: 12 Dec, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This is the header file for the
 *   class ConnectDlg. This class implements
 *   functionality necessary to connect to witness node
 *
 */

#ifndef GUI_WALLET_CONNECTDLG_HPP
#define GUI_WALLET_CONNECTDLG_HPP

#include <QDialog>
#include <string>
#include <QHBoxLayout>
#include <QTableWidget>
#include <graphene/wallet/wallet.hpp>
#include <thread>
#include <vector>

namespace gui_wallet
{

class ConnectDlg : public QDialog
{
    Q_OBJECT

    enum{RPC_ENDPOINT_FIELD,CHAIN_ID_FIELD,CONNECT_BUTTON_FIELD,NUM_OF_FIELDS};

    //friend int CreateWallepApiInstance( void* dataContainer );
public:
    ConnectDlg(QWidget* parent);
    virtual ~ConnectDlg();

    graphene::wallet::wallet_api* GetCurApi();

protected:
    void resizeEvent ( QResizeEvent * event );

protected slots:
    void ConnectPushedSlot();

private:
    std::string                       m_wallet_file_name;
    graphene::wallet::wallet_data     m_wdata;
    QHBoxLayout         m_main_layout;
    QTableWidget        m_main_table;
    graphene::wallet::wallet_api* m_pCurApi;
    std::vector<graphene::wallet::wallet_api*>   m_vAllApis;
};

}

#endif // GUI_WALLET_CONNECTDLG_HPP
