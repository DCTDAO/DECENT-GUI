/*
 *	File      : upload_tab.cpp
 *
 *	Created on: 21 Nov 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#include "upload_tab.hpp"
#include <QHeaderView>
#include <stdio.h>

using namespace gui_wallet;
extern int g_nDebugApplication;

#ifndef USE_TABLE_WIDGET
template <typename qtType>
Upload_tab::InfoOneLine<qtType>::InfoOneLine()
{
    //QSize aSize = m_rside_widget.size();

    m_label.resize(400,50);
    //m_rside_widget.resize(aSize.width(),50);
    m_rside_widget.resize(400,50);

    m_main_layout.addWidget(&m_label);
    m_main_layout.addWidget(&m_rside_widget);
    setLayout(&m_main_layout);
}


template <typename qtType>
Upload_tab::InfoOneLine<qtType>::~InfoOneLine()
{
}


template <typename qtType>
void Upload_tab::InfoOneLine<qtType>::SetBothTexts(const char* a_text1,const char* a_text2)
{
    m_label.setText(tr(a_text1));
    m_rside_widget.setText(tr(a_text2));
}

#endif // #ifndef USE_TABLE_WIDGET


////////////////////////////////////////////////////

class qtLabel_test : public QLabel
{
public:
    qtLabel_test(const QString& a_str) : QLabel(a_str){}
    virtual ~qtLabel_test()
    {
        if(g_nDebugApplication){printf("qtLabel_test::~qtLabel_test()\n");}
    }
};

Upload_tab::Upload_tab()
        :
#ifdef USE_TABLE_WIDGET
        m_info_widget(NUMBER_OF_INFO_LINES+1,2),
#endif
        m_synopsis_label(tr("Synopsis")),
        m_infoLayoutHeader(tr("Information about content"))
{
    QPalette pltEdit;
    QLineEdit* pEditForInfo;
    QPushButton* pPushButton;
    m_synopsis_layout.addWidget(&m_synopsis_label);//
    m_synopsis_layout.addWidget(&m_synopsis_text);//

    m_main_layout.addLayout(&m_synopsis_layout);

    m_info_layout.addWidget(&m_infoLayoutHeader);

#ifdef USE_TABLE_WIDGET

    for(int i(0);i<NUMBER_OF_INFO_LINES;++i)
    {
        pEditForInfo = new QLineEdit(s_sStrPairs[i].str2);
        pltEdit = pEditForInfo->palette();
        pltEdit.setColor(QPalette::Base, Qt::white);
        pEditForInfo->setPalette(pltEdit);
        m_info_widget.setCellWidget(i,0,new qtLabel_test(s_sStrPairs[i].str1));
        m_info_widget.setCellWidget(i,1,pEditForInfo);
        //m_Infos[i].SetBothTexts(s_sStrPairs[i].str1,s_sStrPairs[i].str2);
        //m_info_layout.addWidget(&m_Infos[i]);
    }
    pPushButton = new QPushButton("Select path");
    pltEdit = pPushButton->palette();
    pltEdit.setColor(QPalette::Base, Qt::red);
    pltEdit.setColor(QPalette::WindowText, Qt::white);
    pPushButton->setPalette(pltEdit);
    pPushButton->setAutoFillBackground(true);
    m_info_widget.setCellWidget(NUMBER_OF_INFO_LINES,0,new qtLabel_test("Patch"));
    m_info_widget.setCellWidget(NUMBER_OF_INFO_LINES,1,pPushButton);
    //m_Patch.SetBothTexts("Patch","Select path");
    //m_info_layout.addWidget(&m_Patch);

    m_info_widget.horizontalHeader()->hide();
    m_info_widget.verticalHeader()->hide();
    m_info_layout.addWidget(&m_info_widget);
    m_info_widget.setShowGrid(false);
    QPalette plt_tbl = m_info_widget.palette();
    plt_tbl.setColor(QPalette::Base, palette().color(QPalette::Window));
    m_info_widget.setPalette(plt_tbl);

#else   // #ifdef USE_TABLE_WIDGET
    for(int i(0);i<NUMBER_OF_INFO_LINES;++i)
    {
        m_Infos[i].SetBothTexts(s_sStrPairs[i].str1,s_sStrPairs[i].str2);
        m_info_layout.addWidget(&m_Infos[i]);
    }
    m_Patch.SetBothTexts("Patch","Select path");
    m_info_layout.addWidget(&m_Patch);
#endif  // #ifdef USE_TABLE_WIDGET

    m_main_layout.addLayout(&m_info_layout);

    setLayout(&m_main_layout);
}


Upload_tab::~Upload_tab()
{
}


void Upload_tab::resizeEvent ( QResizeEvent * event )
{
    QWidget::resizeEvent(event);

    QSize aInfWidgSize = m_info_widget.size();

    m_info_widget.setColumnWidth(0,39*aInfWidgSize.width()/100);
    m_info_widget.setColumnWidth(1,59*aInfWidgSize.width()/100);

}
