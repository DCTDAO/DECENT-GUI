/*
 *	File: gui_wallet_centralwigdet.cpp
 *
 *	Created on: Nov 11, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */

#define DECENT_LOGO_FILE_NAME   "dc_logo.jpg"

#include "gui_wallet_centralwigdet.hpp"
#include <QMessageBox>
#include <QTimer>

using namespace gui_wallet;

CentralWigdet::CentralWigdet()
{
}


CentralWigdet::~CentralWigdet()
{
}


void CentralWigdet::showEvent ( QShowEvent * event )
{
    QWidget::showEvent(event);

    m_main_tabs.addTab(&m_browse_cont_tab,tr("BROWSE CONTENT"));
    m_main_tabs.addTab(&m_trans_tab,tr("TRANSACTIONS"));
    m_main_tabs.addTab(&m_Upload_tab,tr("UPLOAD"));
    m_main_tabs.addTab(&m_Overview_tab,tr("OVERVIEW"));

    QLabel* imageLabel = new QLabel;
    QPixmap image;
    if( image.load(DECENT_LOGO_FILE_NAME) )
    {
        imageLabel->setPixmap(image);
    }
    else
    {
        m_DelayedWaringTitle = tr("no logo file");
        m_DelayedWaringText = tr(DECENT_LOGO_FILE_NAME" file can not be found!");
        m_DelayedWaringDetails = tr(
                "for current implementation "DECENT_LOGO_FILE_NAME"file is searched"
                "in current working directory");
        QTimer::singleShot(100, this, SLOT(make_deleyed_warning()));
        imageLabel->setText("DC");
    }

    QPalette plt_fst_ln_w = m_first_line_widget.palette();
    plt_fst_ln_w.setColor(QPalette::Window,Qt::black);
    //plt_fst_ln_w.setColor(QPalette::Base,Qt::black);
    m_first_line_widget.setPalette(plt_fst_ln_w);

    //m_first_line_layout.setS

    m_first_line_layout.addWidget(imageLabel);
    m_first_line_layout.addWidget(&m_search_box);
    m_first_line_widget.setLayout(&m_first_line_layout);

    m_main_layout.addWidget(&m_first_line_widget);
    m_main_layout.addWidget(&m_main_tabs);
    setLayout(&m_main_layout);
}


void CentralWigdet::make_deleyed_warning()
{
    makeWarningImediatly(m_DelayedWaringTitle,m_DelayedWaringText,m_DelayedWaringDetails);
}


void CentralWigdet::makeWarningImediatly(const QString& a_WaringTitle, const QString& a_WaringText, const QString& a_detailed )
{
    QMessageBox aMessageBox(QMessageBox::Warning,a_WaringTitle,a_WaringText,QMessageBox::Ok,this);
    aMessageBox.setDetailedText(a_detailed);
    aMessageBox.exec();
}
