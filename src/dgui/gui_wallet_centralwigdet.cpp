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
#include <QHeaderView>
#include <QResizeEvent>
#include <QScrollBar>

using namespace gui_wallet;

CentralWigdet::CentralWigdet()
        :
        m_first_line_twidget(3,5)
{
    m_imageLabel = new QLabel;
    PrepareGUIprivate();
}


CentralWigdet::~CentralWigdet()
{
    //delete m_imageLabel;
}


void CentralWigdet::PrepareGUIprivate()
{
    m_main_tabs.addTab(&m_browse_cont_tab,tr("BROWSE CONTENT"));
    m_main_tabs.addTab(&m_trans_tab,tr("TRANSACTIONS"));
    m_main_tabs.addTab(&m_Upload_tab,tr("UPLOAD"));
    m_main_tabs.addTab(&m_Overview_tab,tr("OVERVIEW"));

    QPixmap image;
    if( image.load(DECENT_LOGO_FILE_NAME) )
    {
        m_imageLabel->setPixmap(image);
    }
    else
    {
        m_DelayedWaringTitle = tr("no logo file");
        m_DelayedWaringText = tr(DECENT_LOGO_FILE_NAME" file can not be found!");
        m_DelayedWaringDetails = tr(
                "for current implementation "DECENT_LOGO_FILE_NAME"file is searched"
                "in current working directory");
        QTimer::singleShot(100, this, SLOT(make_deleyed_warning()));
        m_imageLabel->setText("DC");
    }

    //m_first_line_layout.setS
#ifdef USE_TABLE_FOR_FIRST_LINE
    m_first_line_twidget.horizontalHeader()->hide();
    m_first_line_twidget.verticalHeader()->hide();
    m_first_line_twidget.verticalScrollBar()->hide();
    m_first_line_twidget.setCellWidget(1,0,m_imageLabel);
    m_first_line_twidget.setCellWidget(1,2,&m_search_box);
    m_main_layout.addWidget(&m_first_line_twidget);
    QSize aImgLbSize = m_imageLabel->size();
    m_first_line_twidget.setFixedHeight(/*event->size().width()-4,*/aImgLbSize.height()+24);
    m_first_line_twidget.setRowHeight(0,10);
    m_first_line_twidget.setRowHeight(1,aImgLbSize.height());
    m_first_line_twidget.setRowHeight(2,10);
    m_first_line_twidget.setColumnWidth(0,aImgLbSize.width());
    m_first_line_twidget.setColumnWidth(1,20);
    m_first_line_twidget.setColumnWidth(2,350);

    QPalette plt = m_first_line_twidget.palette();
    plt.setColor(QPalette::Base, Qt::black);
    plt.setColor(QPalette::Window, Qt::black);
    m_first_line_twidget.setPalette(plt);
    plt = m_search_box.palette();
    plt.setColor(QPalette::Base, Qt::white);
    m_search_box.setPalette(plt);
    m_first_line_twidget.setShowGrid(false);
    //m_first_line_twidget.setShown(false);
#else
    QPalette plt_fst_ln_w = m_first_line_widget.palette();
    plt_fst_ln_w.setColor(QPalette::Window,Qt::black);
    m_first_line_widget.setPalette(plt_fst_ln_w);

    m_first_line_layout.addWidget(imageLabel);
    m_first_line_layout.addWidget(&m_search_box);
    m_first_line_widget.setLayout(&m_first_line_layout);
    m_main_layout.addWidget(&m_first_line_widget);
#endif
    m_main_layout.addWidget(&m_main_tabs);
    setLayout(&m_main_layout);
}


void CentralWigdet::showEvent ( QShowEvent * event )
{
    QWidget::showEvent(event);
    // PrepareGUIprivate();
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


void CentralWigdet::resizeEvent ( QResizeEvent * event )
{
    QWidget::resizeEvent(event);
#if 0
    QSize aImgLbSize = m_imageLabel->size();

    m_first_line_twidget.setFixedHeight(/*event->size().width()-4,*/aImgLbSize.height());
    m_first_line_twidget.setRowHeight(0,aImgLbSize.height());
    m_first_line_twidget.setColumnWidth(0,aImgLbSize.width());
#endif

}
