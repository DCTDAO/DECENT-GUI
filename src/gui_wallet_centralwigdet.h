/*
 *	File: centralwigdet_gui_wallet.h
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
#include "browse_content_tab.h"

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
    };
}



#endif // CENTRALWIGDET_GUI_WALLET_H
