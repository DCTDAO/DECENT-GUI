/*
 *	File: centralwigdet_gui_wallet.cpp
 *
 *	Created on: Nov 11, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#include "gui_wallet_centralwigdet.h"

using namespace gui_wallet;

CentralWigdet::CentralWigdet()
{
    m_main_tabs.addTab(&m_browse_cont_tab,tr("BROWSE CONTENT"));
    m_main_tabs.addTab(new QWidget,tr("TRANSACTIONS"));
    m_main_tabs.addTab(new QWidget,tr("UPLOAD"));
    m_main_tabs.addTab(new QWidget,tr("OVERVIEW"));

    m_first_line.addWidget(&m_search_box);

    m_main_layout.addLayout(&m_first_line);
    m_main_layout.addWidget(&m_main_tabs);
    setLayout(&m_main_layout);
}

CentralWigdet::~CentralWigdet()
{
}
