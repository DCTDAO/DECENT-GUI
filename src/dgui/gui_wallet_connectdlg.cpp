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

#include "gui_wallet_connectdlg.hpp"
#include "connected_api_instance.hpp"
#include <QLineEdit>
#include <QPushButton>
#include <QHeaderView>
#include <thread>
#include <QLabel>

namespace gui_wallet
{


/* ///////////////////////////////////  */
ConnectDlg::ConnectDlg(QWidget* a_parent)
    :
      QDialog(a_parent),
      m_wallet_file_name("wallet.json"),
      m_main_table(NUM_OF_FIELDS,2)
{
    //m_wdata.chain_id = (chain_id_type)0;

    m_main_table.setItem(RPC_ENDPOINT_FIELD,0,new QTableWidgetItem(tr("rpc-endpoint")));
    m_main_table.setCellWidget(RPC_ENDPOINT_FIELD,1,new QLineEdit(tr("ws://127.0.0.1:8090")));

    m_main_table.setItem(CHAIN_ID_FIELD,0,new QTableWidgetItem(tr("chain-id")));
    m_main_table.setCellWidget(CHAIN_ID_FIELD,1,new QLineEdit(tr("d9561465fd1aab95eb6fec9a60705e983b7759ea4c9892ac4acd30737f5079b4")));

    //m_main_table.setItem(FIELDS-1,0,new QTableWidgetItem(tr("rpc-endpoint")));
    m_main_table.setCellWidget(CONNECT_BUTTON_FIELD,0,new QLabel);
    m_main_table.setCellWidget(CONNECT_BUTTON_FIELD,1,new QPushButton(tr("Connect")));

    QPalette aPalette = m_main_table.cellWidget(CONNECT_BUTTON_FIELD,0)->palette();
    aPalette.setColor(QPalette::Base,Qt::gray);
    m_main_table.cellWidget(CONNECT_BUTTON_FIELD,0)->setPalette(aPalette);

    m_main_table.horizontalHeader()->hide();
    m_main_table.verticalHeader()->hide();
    m_main_table.resize(size());
    m_main_layout.addWidget(&m_main_table);
    setLayout(&m_main_layout);

    /* Initing signal-slot pairs*/
    connect( m_main_table.cellWidget(CONNECT_BUTTON_FIELD,1), SIGNAL(clicked()), this, SLOT(ConnectPushedSlot()) );
}


ConnectDlg::~ConnectDlg()
{
}


void ConnectDlg::resizeEvent ( QResizeEvent * event )
{
    QWidget::resizeEvent(event);

    QSize aInfWidgSize = m_main_table.size();

    m_main_table.setColumnWidth(0,40*aInfWidgSize.width()/100);
    m_main_table.setColumnWidth(1,59*aInfWidgSize.width()/100);

}


void ConnectDlg::ConnectPushedSlot()
{

    QString aRpcEndPointAStr = ((QLineEdit*)m_main_table.cellWidget(RPC_ENDPOINT_FIELD,1))->text();
    QByteArray aLatin=aRpcEndPointAStr.toLatin1();
    m_wdata.ws_server = aLatin.data();
    m_wdata.chain_id = chain_id_type( std::string( (((QLineEdit*)m_main_table.cellWidget(CHAIN_ID_FIELD,1))->text()).toLatin1().data() ) );
    std::thread aThread(CreateConnectedApiInstance,&m_wdata,m_wallet_file_name);
    aThread.detach();
    //close();
}

}
