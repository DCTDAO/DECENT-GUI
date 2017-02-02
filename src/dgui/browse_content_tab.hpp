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
#include <QTableWidget>
#include <QVBoxLayout>
#include <vector>

namespace gui_wallet
{

    // DGF stands for Digital Contex Fields
    namespace DGF {enum DIG_CONT_FIELDS{IS_SELECTED,TIME,SYNOPSIS,RATING,LEFT,SIZE,PRICE};}

    struct SDigitalContent{
        std::string author;
        struct{
            double amount;
            std::string asset_id;
        }price;
        std::string synopsis;
        std::string URI;
        double AVG_rating;
    };


    template <typename QtType>
    class TableWidgetItemW : public QtType
    {
    public:
        template <typename ConstrArgType>
        TableWidgetItemW(ConstrArgType a_cons_arg):QtType(a_cons_arg){}
        TableWidgetItemW();
        virtual ~TableWidgetItemW();
    };


    class Browse_content_tab : public QWidget
    {    
    public:
        Browse_content_tab();
        virtual ~Browse_content_tab();

        void showEvent ( QShowEvent * event )  ;

        //QTableWidget& getDigitalContentsTable();
        void SetDigitalContentsGUI(const std::vector<gui_wallet::SDigitalContent>& contents);

    protected:
        void PrepareTableWidgetHeaderGUI();

    protected:
        QVBoxLayout     m_main_layout;
        //QTableWidget    m_TableWidget; // Should be investigated
        QTableWidget*    m_pTableWidget;
        //int              m_nNumberOfContentsPlus1;
    };
}

#endif // BROWSE_CONTENT_TAB_H
