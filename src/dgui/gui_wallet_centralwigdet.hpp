/*
 *	File: gui_wallet_centralwigdet.h
 *
 *	Created on: Nov 11, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef CENTRALWIGDET_GUI_WALLET_H
#define CENTRALWIGDET_GUI_WALLET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTabWidget>
#include "browse_content_tab.hpp"
#include "transactions_tab.hpp"
#include "upload_tab.hpp"
#include "overview_tab.hpp"

namespace gui_wallet
{
    //class Centralwigdet_gui_wallet : public QWidget
    class CentralWigdet : public QWidget
    {
    public:
        CentralWigdet();
        virtual ~CentralWigdet(); // virtual because may be this class will be
                                  // used by inheritance

    private:
        QVBoxLayout         m_main_layout;
        QHBoxLayout         m_first_line;
        QLineEdit           m_search_box;
        QTabWidget          m_main_tabs;
        Browse_content_tab  m_browse_cont_tab;
        Transactions_tab    m_trans_tab;
        Upload_tab          m_Upload_tab;
        Overview_tab        m_Overview_tab;
    };
}



#endif // CENTRALWIGDET_GUI_WALLET_H
