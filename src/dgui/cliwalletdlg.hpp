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
#include <string>

#ifndef __THISCALL__
#ifdef __MSC_VER
#define __THISCALL__ __thiscall
#else  // #ifdef __MSC_VER
#define __THISCALL__
#endif  // #ifdef __MSC_VER
#endif  // #ifndef __THISCALL__

#ifndef CLI_NEW_LINE_FNC_defined
#define CLI_NEW_LINE_FNC_defined
typedef void (__THISCALL__ *CLI_NEW_LINE_FNC)(void*owner,void*arg,const std::string& a_task);
#endif

namespace gui_wallet
{

class CliTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    CliTextEdit(QWidget* pParent);
    virtual ~CliTextEdit();

public:
signals:
    void NewCommandSig(std::string line);

protected:
    virtual void keyReleaseEvent ( QKeyEvent * event );
    virtual void keyPressEvent( QKeyEvent * a_event );
};


/**************************************************************/

class CliWalletDlg : protected QDialog
{
    Q_OBJECT

public:
    CliWalletDlg();
    virtual ~CliWalletDlg();

    template <typename Type>
    void execCli(Type* a_obj_ptr,void* a_callbackArg,void (Type::*a_fpFunction)(void*arg,const std::string& task))
    {
        execCli_base(a_obj_ptr,a_callbackArg,a_fpFunction);
    }

    void execCli(void* owner, void* callbackArg,CLI_NEW_LINE_FNC fpCallback);

protected slots:
    void NewCommandSlot(std::string line);

protected:
    virtual void resizeEvent(QResizeEvent * event );
    void execCli_base(void* owner, void* callbackArg,...);

protected:
    CliTextEdit         m_main_textbox;
    void*               m_pOwner;
    void*               m_pCallbackArg;
    CLI_NEW_LINE_FNC    m_fpTaskDone;
};

}

#endif // CLIWALLETDLG_HPP
