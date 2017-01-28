/*
 *	File: cliwalletdlg.cpp
 *
 *	Created on: 28 Jan 2017
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */


#include "cliwalletdlg.hpp"
#include <QResizeEvent>
#include <QKeyEvent>

extern int g_nDebugApplication;


gui_wallet::CliTextEdit::CliTextEdit(QWidget* a_pParent)
    :
      QTextEdit(a_pParent)
{
    setText(tr(">>>"));
    moveCursor(QTextCursor::End);
}


gui_wallet::CliTextEdit::~CliTextEdit()
{
    //
}


void gui_wallet::CliTextEdit::keyReleaseEvent ( QKeyEvent * a_event )
{
    if(g_nDebugApplication){printf("CliTextEdit::keyReleaseEvent: key=0x%x\n",(int)a_event->key());}
    switch(a_event->key())
    {
    case Qt::Key_Enter: case Qt::Key_Return:
        if(g_nDebugApplication){printf("Qt::Key_Enter\n");}
        QTextEdit::keyReleaseEvent(a_event);
        append(tr(">>>"));
        moveCursor(QTextCursor::End);
        break;
    case Qt::Key_Backspace:
    {
        QTextCursor cCursor = textCursor();
        int nColumnNumber = cCursor.columnNumber();
        if(nColumnNumber>3)
        {
            QTextEdit::keyReleaseEvent(a_event);
        }
    }
        break;
    default:
        if(g_nDebugApplication){printf("default\n");}
        QTextEdit::keyReleaseEvent(a_event);
        break;
    }
}


/***************************************************************/

gui_wallet::CliWalletDlg::CliWalletDlg()
    : m_main_textbox(this)
{
    resize(500,300);
}


gui_wallet::CliWalletDlg::~CliWalletDlg()
{
    //
}


void gui_wallet::CliWalletDlg::resizeEvent(QResizeEvent * a_event )
{
    QDialog::resizeEvent(a_event);
    m_main_textbox.resize(a_event->size());
}
