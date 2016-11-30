/*
 *	File: gui_wallet_centralwigdet.cpp
 *
 *	Created on: Nov 11, 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */

#define DECENT_LOGO_FILE_NAME       "dc_logo.jpg"
#define DECENT_LOGO_INITIAL_PATH    "../../../images/"

#include "gui_wallet_centralwigdet.hpp"
#include <QMessageBox>
#include <QTimer>
#include <QHeaderView>
#include <QResizeEvent>
#include <QScrollBar>
#include "gui_wallet_global.hpp"


using namespace gui_wallet;

CentralWigdet::CentralWigdet()
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
    bool bImageFound(true);
    m_main_tabs.addTab(&m_browse_cont_tab,tr("BROWSE CONTENT"));
    m_main_tabs.addTab(&m_trans_tab,tr("TRANSACTIONS"));
    m_main_tabs.addTab(&m_Upload_tab,tr("UPLOAD"));
    m_main_tabs.addTab(&m_Overview_tab,tr("OVERVIEW"));

    QPixmap image;
    if( !image.load(DECENT_LOGO_INITIAL_PATH DECENT_LOGO_FILE_NAME) )
    {
        // Search for couple of other places
        if( !image.load("./" DECENT_LOGO_FILE_NAME) )
        {
            if( !image.load("./" DECENT_LOGO_FILE_NAME) )
            {
                if( !image.load(DECENT_LOGO_FILE_NAME) ){bImageFound = false;}
            }
        }
    }

    if(bImageFound){m_imageLabel->setPixmap(image);}
    else
    {   
        m_DelayedWaringTitle = tr("no logo file");
        m_DelayedWaringText = tr(DECENT_LOGO_FILE_NAME" file can not be found!");
        m_DelayedWaringDetails = tr(
                "file '"DECENT_LOGO_FILE_NAME"' could not be found\n"
                "The search paths are the following:\n"
                "1. the current directory \n"
                "2. the 'image'' folder in the current directory\n"
                "3. the 'image'' folder in the \"../../../\"\n"
                "To see the logo, please put the logo file to the directories\n"
                "mentioned above and then rerun the application");
        QTimer::singleShot(100, this, SLOT(make_deleyed_warning()));
        m_imageLabel->setText("DC");
    }

    m_first_line_widget.setStyleSheet("background-color:black;");
    m_search_box.setStyleSheet("background-color:white;");

    m_first_line_layout.addWidget(m_imageLabel);
    m_first_line_layout.addWidget(&m_search_box);
    m_first_line_widget.setLayout(&m_first_line_layout);
    m_main_layout.addWidget(&m_first_line_widget);

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
    gui_wallet::makeWarningImediatly(m_DelayedWaringTitle.toLatin1().data(),
                                     m_DelayedWaringText.toLatin1().data(),
                                     m_DelayedWaringDetails.toLatin1().data(),this);
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
