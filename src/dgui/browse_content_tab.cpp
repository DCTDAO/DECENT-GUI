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
#include <QRadioButton>
#include <stdio.h>

using namespace gui_wallet;
extern int g_nDebugApplication;


Browse_content_tab::Browse_content_tab()
        :
        m_TableWidget(0,7)
{
    //QLayout* pMainLayout = layout();
    //pMainLayout->addWidget(&m_TableWidget);

    //printf("fl:%s, ln:%d\n",__FILE__,__LINE__);

    m_main_layout.addWidget(&m_TableWidget);
    setLayout(&m_main_layout);
}

class TableWidgetItem_test : public QTableWidgetItem
{
public:
    TableWidgetItem_test(const QString& a_str) : QTableWidgetItem(a_str){}
    virtual ~TableWidgetItem_test()
    {
        if(g_nDebugApplication){printf("TableWidgetItem_test::~TableWidgetItem_test()\n");}
    }
};


void Browse_content_tab::showEvent ( QShowEvent * event )
{
    QTableWidgetItem* pItem;

    QWidget::showEvent(event);

    pItem = new TableWidgetItem_test(tr(""));
    if(!pItem){/*warn on low memory*/return;}
    m_TableWidget.setHorizontalHeaderItem(0,pItem);

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

    /*QTableWidget aTbWidget(1,1);
    QRadioButton* pRadio = new QRadioButton;
    QTableWidgetItem* pItem00 = new QTableWidgetItem;
    //pItem0->setVar
    aTbWidget.setItem(0,0,pItem00);
    pRadio->show();
    aTbWidget.setCellWidget(0,0,pRadio);
    printf("point1\n");
    QTableWidgetItem * pItem0 = aTbWidget.item(0,0);
    printf("point2(%p)\n",pItem0);
    s_pItem = pItem0->clone();
    printf("point2\n");
    m_TableWidget.setHorizontalHeaderItem(0,s_pItem);
    //m_TableWidget.setHorizontalHeader*/
    //m_TableWidget.setCellWidget(0,0,new QRadioButton);

    //m_TableWidget.setCellWidget(0,0,new QRadioButton);
    //m_TableWidget.cellWidget(0,0)->show();
}

Browse_content_tab::~Browse_content_tab()
{
}
