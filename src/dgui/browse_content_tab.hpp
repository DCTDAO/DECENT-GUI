/*
 *	File: browse_content_tab.hpp
 *
 *	Created on: 11 Nov 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef BROWSE_CONTENT_TAB_H
#define BROWSE_CONTENT_TAB_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

namespace gui_wallet
{
    class Browse_content_tab : public QWidget
    {    
    public:
        Browse_content_tab();
        virtual ~Browse_content_tab();

    private:
        QHBoxLayout m_main_layout;
        QVBoxLayout m_synopsis_layout;
        QVBoxLayout m_info_layout;
        QLabel      m_synopsis_label;
        QTextEdit   m_synopsis_text;
    };
}

#endif // BROWSE_CONTENT_TAB_H
