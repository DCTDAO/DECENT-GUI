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
#include <stdarg.h>
#include <QTextBlock>

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
#if 0
#else
    QTextEdit::keyReleaseEvent(a_event);
#endif
}


void gui_wallet::CliTextEdit::keyPressEvent( QKeyEvent * a_event )
{
    QTextCursor cCursor = textCursor();
    int nColumnNumber = cCursor.columnNumber();

    if(g_nDebugApplication){printf("CliTextEdit::keyPressEvent: key=0x%x, col_num=%d\n",(int)a_event->key(),nColumnNumber);}

    if(nColumnNumber<3){return;}

    switch(a_event->key())
    {
    case Qt::Key_Enter: case Qt::Key_Return:
    {
        QTextDocument* pTextDoc = document();
        int nLastLinePlus1 = pTextDoc->lineCount();
        QTextBlock cLastBlock = pTextDoc->findBlockByLineNumber(nLastLinePlus1-1);
        QString cqsLastLine = cLastBlock.text();
        QByteArray cbaBlock = cqsLastLine.toLatin1();
        std::string csLastBlockStr = cbaBlock.data();
        if(g_nDebugApplication){printf("Qt::Key_Enter, nLastLinePlus1=%d\n",nLastLinePlus1);}
        QTextEdit::keyPressEvent(a_event);
        append(tr(">>>"));
        moveCursor(QTextCursor::End);

        emit NewCommandSig(csLastBlockStr.c_str()+3);
        break;
    }
    case Qt::Key_Backspace:
    {
        if(g_nDebugApplication){printf("Qt::Key_Backspace:\n");}
        if(nColumnNumber>3)
        {
            QTextEdit::keyPressEvent(a_event);
        }
    }
        break;
    default:
        if(g_nDebugApplication){printf("default\n");}
        QTextEdit::keyPressEvent(a_event);
        break;
    }
}


/***************************************************************/

gui_wallet::CliWalletDlg::CliWalletDlg()
    : m_main_textbox(this)
{
    resize(500,300);

    connect(&m_main_textbox,SIGNAL(NewCommandSig(std::string)),this,SLOT(NewCommandSlot(std::string)));
}


gui_wallet::CliWalletDlg::~CliWalletDlg()
{
    //
}


void gui_wallet::CliWalletDlg::NewCommandSlot(std::string a_line)
{
    (*m_fpTaskDone)(m_pOwner,m_pCallbackArg,a_line);
}


void gui_wallet::CliWalletDlg::resizeEvent(QResizeEvent * a_event )
{
    QDialog::resizeEvent(a_event);
    m_main_textbox.resize(a_event->size());
}


void gui_wallet::CliWalletDlg::execCli(void* a_owner, void* a_callbackArg,CLI_NEW_LINE_FNC a_fpCallback)
{
    execCli_base(a_owner,a_callbackArg,a_fpCallback);
}

void gui_wallet::CliWalletDlg::execCli_base(void* a_owner, void* a_callbackArg,...)
{
    va_list aFunc;

    va_start( aFunc, a_callbackArg );  /* Initialize variable arguments. */
    m_fpTaskDone = va_arg( aFunc, CLI_NEW_LINE_FNC);
    va_end( aFunc );                /* Reset variable arguments.      */

    m_pOwner = a_owner;
    m_pCallbackArg = a_callbackArg;

    QDialog::exec();
}
