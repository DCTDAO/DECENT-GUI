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

typedef void (*WaletFncType)(/*class graphene::wallet::wallet_api*/void* wa,void*ud);

namespace gui_wallet
{

int CreateWallepApiInstance( void* dataContainer );
void UseWalletApiInstance(WaletFncType fpFunction, void* userData);

class ConnectDlg : public QDialog
{
    Q_OBJECT

    //friend int CreateWallepApiInstance( void* dataContainer );
    friend int CreateWallepApiInstance( void* a_dataContainer );
public:
    ConnectDlg();
    virtual ~ConnectDlg();

protected:
    void resizeEvent ( QResizeEvent * event );

protected slots:
    void ConnectPushedSlot();

private:
    std::string                                     m_wallet_file_name;
    /*struct graphene::wallet::wallet_data*/void*   m_pWdata;
    QHBoxLayout         m_main_layout;
    QTableWidget        m_main_table;
    class QLineEdit*    m_pRpcEndpointEdit;
    class QPushButton*  m_pConnectButton;
};

}

#endif // GUI_WALLET_CONNECTDLG_HPP
