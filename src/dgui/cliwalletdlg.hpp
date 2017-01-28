/*
 *	File: cliwalletdlg.hpp
 *
 *	Created on: 28 Jan 2017
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef CLIWALLETDLG_HPP
#define CLIWALLETDLG_HPP

#include <QDialog>
#include <QTextEdit>

namespace gui_wallet
{

class CliTextEdit : public QTextEdit
{
public:
    CliTextEdit(QWidget* pParent);
    virtual ~CliTextEdit();

protected:
    virtual void keyReleaseEvent ( QKeyEvent * event );
};

class CliWalletDlg : public QDialog
{
public:
    CliWalletDlg();
    virtual ~CliWalletDlg();

protected:
    virtual void resizeEvent(QResizeEvent * event );

protected:
    CliTextEdit   m_main_textbox;
};

}

#endif // CLIWALLETDLG_HPP
