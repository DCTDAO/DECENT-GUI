/*
 *	File: browse_content_tab.cpp
 *
 *	Created on: 11 Nov 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#include "browse_content_tab.hpp"
#include <QLayout>
#include <QCheckBox>
#include <stdio.h>
#include <QHeaderView>
#include <QLabel>

#if 0
pItem = new TableWidgetItem_test(tr("Time"));
if(!pItem){/*warn on low memory*/return;}
m_TableWidget.setHorizontalHeaderItem(1,pItem);

pItem = new TableWidgetItem_test(tr("Synopsis"));
if(!pItem){/*warn on low memory*/return;}
m_TableWidget.setHorizontalHeaderItem(2,pItem);

pItem = new TableWidgetItem_test(tr("Rating"));
if(!pItem){/*warn on low memory*/return;}
m_TableWidget.setHorizontalHeaderItem(3,pItem);

pItem = new TableWidgetItem_test(tr("Left"));
if(!pItem){/*warn on low memory*/return;}
m_TableWidget.setHorizontalHeaderItem(4,pItem);

pItem = new TableWidgetItem_test(tr("Size"));
if(!pItem){/*warn on low memory*/return;}
m_TableWidget.setHorizontalHeaderItem(5,pItem);

pItem = new TableWidgetItem_test(tr("Price"));
if(!pItem){/*warn on low memory*/return;}
m_TableWidget.setHorizontalHeaderItem(6,pItem);
#endif

static const char* s_vccpItemNames[]={"","Time","Synopsis","Rating",
                                     "Left","Size","Price"};
static const int   s_cnNumberOfRows = sizeof(s_vccpItemNames)/sizeof(const char*);

using namespace gui_wallet;
extern int g_nDebugApplication;


/********************************************************************************/
/************ class TableWidgetItemW ********************************************/
/********************************************************************************/

/*
template <typename QtType,typename ConstrArgType>
gui_wallet::TableWidgetItemW<QtType>::TableWidgetItemW(ConstrArgType a_cons_arg)
    :
      QtType(a_cons_arg)
{
}
*/

template <typename QtType>
gui_wallet::TableWidgetItemW<QtType>::TableWidgetItemW()
{
}

template <typename QtType>
gui_wallet::TableWidgetItemW<QtType>::~TableWidgetItemW()
{
    if(g_nDebugApplication){printf("!!! fn:%s, ln%d\n",__FUNCTION__,__LINE__);}
}


/********************************************************************************/
/************ class Browse_content_tab ******************************************/
/********************************************************************************/

Browse_content_tab::Browse_content_tab()
        :
        //m_TableWidget(1,s_cnNumberOfRows)
        m_pTableWidget(new QTableWidget(1,s_cnNumberOfRows))
{
    if(!m_pTableWidget){throw "Low memory!";}

    PrepareTableWidgetHeaderGUI();

    m_main_layout.addWidget(m_pTableWidget);
    setLayout(&m_main_layout);


}


Browse_content_tab::~Browse_content_tab()
{
    m_main_layout.removeWidget(m_pTableWidget);
    delete m_pTableWidget;
}


void Browse_content_tab::PrepareTableWidgetHeaderGUI()
{
    QTableWidget& m_TableWidget = *m_pTableWidget;
    TableWidgetItemW<QLabel>* pLabel;
    m_TableWidget.horizontalHeader()->hide();
    m_TableWidget.verticalHeader()->hide();

    TableWidgetItemW<QCheckBox>* pCheck = new TableWidgetItemW<QCheckBox>;
    m_TableWidget.setCellWidget(0,DGF::IS_SELECTED,pCheck);

    for( int i(1); i<s_cnNumberOfRows; ++i )
    {
        pLabel = new TableWidgetItemW<QLabel>(tr(s_vccpItemNames[i]));
        m_TableWidget.setCellWidget(0,i,pLabel);
    }

    QPalette plt_tbl = m_TableWidget.palette();
    plt_tbl.setColor(QPalette::Base, palette().color(QPalette::Window));
    m_TableWidget.setPalette(plt_tbl);
}


void Browse_content_tab::showEvent ( QShowEvent * event )
{
    QWidget::showEvent(event);
}


void Browse_content_tab::SetDigitalContentsGUI(const std::vector<gui_wallet::SDigitalContent>& a_vContents)
{
    //
    QCheckBox* pCheck;
    QLabel* pLabel;
    gui_wallet::SDigitalContent aTemporar;
    const int cnNumberOfContentsPlus1((int)a_vContents.size() + 1);

    if(g_nDebugApplication){printf("cnNumberOfContentsPlus1=%d\n",cnNumberOfContentsPlus1);}

    //m_TableWidget.setColumnCount(cnNumberOfContentsPlus1);

    m_main_layout.removeWidget(m_pTableWidget);
    delete m_pTableWidget;
    m_pTableWidget = new QTableWidget(cnNumberOfContentsPlus1,s_cnNumberOfRows);
    if(!m_pTableWidget){throw "Low memory!";}

    QTableWidget& m_TableWidget = *m_pTableWidget;

    PrepareTableWidgetHeaderGUI();

    for(int i(1); i<cnNumberOfContentsPlus1; ++i)
    {
        if(g_nDebugApplication){printf("fn:%s, ln:%d, i=%d\n",__FUNCTION__,__LINE__,i);}
        aTemporar = a_vContents[i-1];
        // To be continue
        // namespace DGF {enum DIG_CONT_FIELDS{IS_SELECTED,TIME,SYNOPSIS,RATING,LEFT,SIZE,PRICE};}
        pCheck = new QCheckBox;
        if(!pCheck){throw "Low memory!";}
        m_TableWidget.setCellWidget(i,DGF::IS_SELECTED,pCheck);

        pLabel = new QLabel(tr("1970.01.01"));
        if(!pLabel){throw "Low memory!";}
        m_TableWidget.setCellWidget(i,DGF::TIME,pLabel);

        pLabel = new QLabel(tr(aTemporar.synopsis.c_str()));
        if(!pLabel){throw "Low memory!";}
        m_TableWidget.setCellWidget(i,DGF::SYNOPSIS,pLabel);

        pLabel = new QLabel( QString::number(aTemporar.AVG_rating,'f').remove( QRegExp("0+$") ).remove( QRegExp("\\.$") ) );
        if(!pLabel){throw "Low memory!";}
        m_TableWidget.setCellWidget(i,DGF::RATING,pLabel);

        pLabel = new QLabel(tr("left"));
        if(!pLabel){throw "Low memory!";}
        m_TableWidget.setCellWidget(i,DGF::LEFT,pLabel);

        pLabel = new QLabel(tr("1MB"));
        if(!pLabel){throw "Low memory!";}
        m_TableWidget.setCellWidget(i,DGF::SIZE,pLabel);

        pLabel = new QLabel( QString::number(aTemporar.price.amount,'f').remove( QRegExp("0+$") ).remove( QRegExp("\\.$") ) );
        if(!pLabel){throw "Low memory!";}
        m_TableWidget.setCellWidget(i,DGF::PRICE,pLabel);
    }

    if(g_nDebugApplication){printf("fn:%s, ln:%d\n",__FUNCTION__,__LINE__);}
    m_main_layout.addWidget(&m_TableWidget);
}
