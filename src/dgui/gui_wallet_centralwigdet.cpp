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
#define GLOBE_FILE_NAME             "globe.jpg"
#define MAN_LOGO_FILE_NAME          "man_logo.jpg"
#define DECENT_IMGS_INITIAL_PATH    "../../../images/"

#include "gui_wallet_centralwigdet.hpp"
#include <QMessageBox>
#include <QTimer>
#include <QHeaderView>
#include <QResizeEvent>
#include <QScrollBar>
#include "gui_wallet_global.hpp"


using namespace gui_wallet;

CentralWigdet::CentralWigdet()
    :
      m_nBalance(0)
{
    m_imageLabel = new QLabel;
    PrepareGUIprivate();
}


CentralWigdet::~CentralWigdet()
{
    //delete m_imageLabel;
}


void CentralWigdet::SetAccountBalanceGUI(int a_nBallance)
{
    if(a_nBallance>=0){m_nBalance = a_nBallance;}
    QString aBalance = QString::number(m_nBalance,10) + tr(" DTC");
    m_balanceLabel.setText(aBalance);
}


const int& CentralWigdet::GetAccountBalance()const
{
    return m_nBalance;
}



//static void SetImageToLabelStatic(){}
#define SetImageToLabelStatic(_bRet_,_image_,_image_name_) \
        do{ \
            (_bRet_)=true; \
            if( !(_image_).load(DECENT_IMGS_INITIAL_PATH _image_name_) ) {\
                /* Search for couple of other places */ \
                if( !(_image_).load("./" _image_name_) ) {\
                    if( !(_image_).load((_image_name_)) ){(_bRet_)=false;} \
                }\
             }\
        }while(0)



void CentralWigdet::PrepareGUIprivate()
{
    bool bImageFound(true);
    m_main_tabs.addTab(&m_browse_cont_tab,tr("BROWSE CONTENT"));
    m_main_tabs.addTab(&m_trans_tab,tr("TRANSACTIONS"));
    m_main_tabs.addTab(&m_Upload_tab,tr("UPLOAD"));
    m_main_tabs.addTab(&m_Overview_tab,tr("OVERVIEW"));

    QTabBar* pTabBar = m_main_tabs.tabBar();

    pTabBar->setStyleSheet("QTabBar::tab:disabled {"
        "width: 200px;"
        "color: transparent;"
        "background: transparent;"
     "}");
    //pTabBar->setStyleSheet("QTabBar{disabled{width:100px;color:transparent;background:transparent;}}");
    //m_main_tabs.addTab(new QWidget(),tr(""));
    m_main_tabs.addTab(new QWidget(),tr(""));
    m_main_tabs.setTabEnabled(4,false);
    m_main_tabs.setTabEnabled(5,false);
    /* /// Should be fixed, and set to widget of project defined class*/
    QString aSendReceiveText;
#if 0
    wchar_t vwcStr[2]={0};
    vwcStr[0] = 0x2192;
    vwcStr[1] = (wchar_t)0;
    aSendReceiveText.fromWCharArray(vwcStr);
#else
    aSendReceiveText = tr("-> SEND");
    //aSendReceiveText.fromWCharArray(L"Русский");
#endif
    m_main_tabs.addTab(new QWidget(),aSendReceiveText);
    m_main_tabs.addTab(new QWidget(),tr("<- RECEIVE"));

    QPixmap image;

    SetImageToLabelStatic(bImageFound,image,DECENT_LOGO_FILE_NAME);
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
    /* /// Probably should be Modified, to skip new ...! */
    QLabel* pBalanceLabel = new QLabel(tr("Balance"));
    QPalette aPal = pBalanceLabel->palette();
    aPal.setColor(QPalette::Window, Qt::black);
    aPal.setColor(QPalette::WindowText, Qt::white);
    pBalanceLabel->setPalette(aPal);
    m_first_line_layout.addWidget(pBalanceLabel);

    /*/////////////// pGlobeLabel ////////////////////////*/
    QLabel* pGlobeLabel = new QLabel;
    SetImageToLabelStatic(bImageFound,image,GLOBE_FILE_NAME);
    if(bImageFound){pGlobeLabel->setPixmap(image);}
    else
    {
        m_DelayedWaringTitle = tr("no glob file");
        m_DelayedWaringText = tr(GLOBE_FILE_NAME" file can not be found!");
        m_DelayedWaringDetails = tr(
                "file '"GLOBE_FILE_NAME"' could not be found\n"
                "The search paths are the following:\n"
                "1. the current directory \n"
                "2. the 'image'' folder in the current directory\n"
                "3. the 'image'' folder in the \"../../../\"\n"
                "To see the logo, please put the logo file to the directories\n"
                "mentioned above and then rerun the application");
        QTimer::singleShot(100, this, SLOT(make_deleyed_warning()));
        pGlobeLabel->setText("Glb");
    }
    m_first_line_layout.addWidget(pGlobeLabel);
    /*/////////////// end pGlobeLabel ////////////////////*/

    /* /// End Probably should be Modified, to skip new ...! */

    //m_balanceLabel.setText(tr("0 DTC"));
    SetAccountBalanceGUI();
    aPal = m_balanceLabel.palette();
    aPal.setColor(QPalette::Window, Qt::black);
    aPal.setColor(QPalette::WindowText, Qt::white);
    m_balanceLabel.setPalette(aPal);
    m_first_line_layout.addWidget(&m_balanceLabel);

    /*/////////////// pManLabel ////////////////////////*/
    QLabel* pManLabel = new QLabel;
    SetImageToLabelStatic(bImageFound,image,MAN_LOGO_FILE_NAME);
    if(bImageFound){pManLabel->setPixmap(image);}
    else
    {
        m_DelayedWaringTitle = tr("no glob file");
        m_DelayedWaringText = tr(MAN_LOGO_FILE_NAME" file can not be found!");
        m_DelayedWaringDetails = tr(
                "file '"MAN_LOGO_FILE_NAME"' could not be found\n"
                "The search paths are the following:\n"
                "1. the current directory \n"
                "2. the 'image'' folder in the current directory\n"
                "3. the 'image'' folder in the \"../../../\"\n"
                "To see the logo, please put the logo file to the directories\n"
                "mentioned above and then rerun the application");
        QTimer::singleShot(100, this, SLOT(make_deleyed_warning()));
        pManLabel->setText("Man");
    }
    m_first_line_layout.addWidget(pManLabel);
    /*/////////////// end pManLabel ////////////////////*/

    //m_users_list
    m_users_list.setStyleSheet("color: white;""background-color:red;");
    aPal = m_users_list.palette();
    aPal.setColor(QPalette::Window, Qt::red);
    aPal.setColor(QPalette::WindowText, Qt::white);
    m_users_list.setPalette(aPal);
    m_users_list.addItem(tr("Username"));
    m_first_line_layout.addWidget(&m_users_list);

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
