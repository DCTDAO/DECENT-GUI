/*
 *	File      : upload_tab.hpp
 *
 *	Created on: 21 Nov 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef UPLOAD_TAB_HPP
#define UPLOAD_TAB_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

#define USE_TABLE_WIDGET

//#define NUMBER_OF_INFO_LINES    5

namespace gui_wallet
{
    struct SStrPair{const char  *str1,*str2;};
    static const SStrPair s_sStrPairs[] ={{"Lifetime",""},{"Seeders",""},{"Key particles",""},{"Tags","Add tag"},{"Price","0.00"}};
    static const int NUMBER_OF_INFO_LINES = sizeof(s_sStrPairs) / sizeof(struct SStrPair);

    class Upload_tab : public QWidget
    {    
    public:
        Upload_tab();
        virtual ~Upload_tab();

    protected:
        virtual void resizeEvent ( QResizeEvent * event );

    private:
        QHBoxLayout m_main_layout;
        QVBoxLayout m_synopsis_layout;
        QVBoxLayout m_info_layout;
#ifdef USE_TABLE_WIDGET
        QTableWidget    m_info_widget;
#endif  // #ifdef USE_TABLE_WIDGET
        QLabel      m_synopsis_label;
        QTextEdit   m_synopsis_text;
        QLabel      m_infoLayoutHeader;

    private:
#ifdef USE_TABLE_WIDGET
#else   // #ifdef USE_TABLE_WIDGET
        template <typename qtType=QLineEdit>
        class InfoOneLine : public QWidget
        {
        public:
            InfoOneLine();
            ~InfoOneLine();

            void SetBothTexts(const char* /*a_text1*/,const char* /*a_text2*/);

        private:
            QHBoxLayout m_main_layout;
            QLabel      m_label;
            qtType      m_rside_widget;
        };

        InfoOneLine<>               m_Infos[NUMBER_OF_INFO_LINES];
        InfoOneLine<QPushButton>    m_Patch;
#endif  // #ifdef USE_TABLE_WIDGET

    };

}

#endif // UPLOAD_TAB_HPP
