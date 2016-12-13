/*
 *	File: gui_wallet_connectdlg.cpp
 *
 *	Created on: 12 Dec, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  Implementation for
 *   class ConnectDlg. This class implements
 *   functionality necessary to connect to witness node
 *
 */

#define FIELDS  3

#include "gui_wallet_connectdlg.hpp"

#include <graphene/wallet/WALLET.HPP>
#include <fc/network/http/websocket.hpp>
#include <fc/rpc/websocket_api.hpp>
#include <graphene/egenesis/egenesis.hpp>
#include <mutex>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>

using namespace graphene::wallet;
using namespace fc::http;
//using namespace gui_wallet;

//static std::shared_ptr<graphene::wallet::wallet_api>   s_pWallet_api = NULL;
static graphene::wallet::wallet_api*   s_pWallet_api = NULL;
static std::mutex                      s_wallet_mutex;
//static fc::http::websocket_connection* s_pConnection = NULL;
static websocket_connection_ptr        s_con;
static std::shared_ptr<fc::rpc::websocket_api_connection>   s_apic;
static fc::api<graphene::app::login_api>                    s_remote_api;

namespace gui_wallet
{

int CreateWallepApiInstance( void* a_dataContainer )
{
    ConnectDlg* pDlg = (ConnectDlg*)a_dataContainer;
    graphene::wallet::wallet_data& wdata = *((graphene::wallet::wallet_data*)pDlg->m_pWdata);
    fc::path wallet_file( pDlg->m_wallet_file_name );

    if( fc::exists( wallet_file ) )
    {
        wdata = fc::json::from_file( wallet_file ).as<wallet_data>();
#if 0
        if( chain_id_type(options.at("chain-id").as<std::string>()) != wdata.chain_id )
        {
            //std::cout << "Chain ID in wallet file does not match specified chain ID\n";
            return 1;
        }
#endif
    }

    //idump((wdata.ws_server));

    fc::http::websocket_client client;
    //auto con  = client.connect( wdata.ws_server );
    //auto apic = std::make_shared<fc::rpc::websocket_api_connection>(*con);
    s_con = client.connect( wdata.ws_server );
    s_apic = std::make_shared<fc::rpc::websocket_api_connection>(*s_con);
    s_remote_api = s_apic->get_remote_api< login_api >(1);
    //edump((wdata.ws_user)(wdata.ws_password) );
    // TODO:  Error message here
    FC_ASSERT( s_remote_api->login( wdata.ws_user, wdata.ws_password ) );

    //auto wapiptr = std::make_shared<wallet_api>( wdata, remote_api );
    graphene::wallet::wallet_api* wapiptr = new wallet_api(wdata,s_remote_api);

#if 0
    // but allow CLI to override
    if( options.count("server-rpc-endpoint") )
        wdata.ws_server = options.at("server-rpc-endpoint").as<std::string>();
    if( options.count("server-rpc-user") )
        wdata.ws_user = options.at("server-rpc-user").as<std::string>();
    if( options.count("server-rpc-password") )
        wdata.ws_password = options.at("server-rpc-password").as<std::string>();
#endif

    s_wallet_mutex.lock();
    //s_pWallet_api = new graphene::wallet::wallet_api();
    if(s_pWallet_api)
    {
        /* /// Which resources shoulb be freed */
        delete s_pWallet_api;
        s_pWallet_api = NULL;
    }
    s_pWallet_api = wapiptr;
    s_wallet_mutex.unlock();
    return 0;
}


void UseWalletApiInstance(WaletFncType a_fpFunction, void* a_pUserData)
{
    s_wallet_mutex.lock();
    (*a_fpFunction)(s_pWallet_api,a_pUserData);
    s_wallet_mutex.unlock();
}


/* ///////////////////////////////////  */
ConnectDlg::ConnectDlg()
    :
      m_wallet_file_name("wallet.json"),
      m_pWdata(new wallet_data),
      m_main_table(FIELDS,2)
{
    ((graphene::wallet::wallet_data*)m_pWdata)->chain_id = graphene::egenesis::get_egenesis_chain_id();

    m_pRpcEndpointEdit = new QLineEdit(tr("ws://127.0.0.1:8090"));
    m_pConnectButton = new QPushButton(tr("Connect"));

    m_main_table.setItem(0,0,new QTableWidgetItem(tr("rpc-endpoint")));
    m_main_table.setCellWidget(0,1,m_pRpcEndpointEdit);

    //m_main_table.setItem(FIELDS-1,0,new QTableWidgetItem(tr("rpc-endpoint")));
    m_main_table.setCellWidget(FIELDS-1,1,m_pConnectButton);

    m_main_table.horizontalHeader()->hide();
    m_main_table.verticalHeader()->hide();
    m_main_table.resize(size());
    m_main_layout.addWidget(&m_main_table);
    setLayout(&m_main_layout);

    /* Initing signal-slot pairs*/
    connect( m_pConnectButton, SIGNAL(clicked()), this, SLOT(ConnectPushedSlot()) );
}


ConnectDlg::~ConnectDlg()
{
    delete ((graphene::wallet::wallet_data*)m_pWdata);
}


void ConnectDlg::resizeEvent ( QResizeEvent * event )
{
    QWidget::resizeEvent(event);

    QSize aInfWidgSize = m_main_table.size();

    m_main_table.setColumnWidth(0,40*aInfWidgSize.width()/100);
    m_main_table.setColumnWidth(1,59*aInfWidgSize.width()/100);

}

#include <stdio.h>

void ConnectDlg::ConnectPushedSlot()
{
    //printf("hi\n");
    try
    {
        CreateWallepApiInstance(this);
    }
    catch(const fc::exception& a_fc)
    {
        printf("%s\n",(a_fc.to_detail_string()).c_str());
    }
    catch(...)
    {}
    close();
}

}
