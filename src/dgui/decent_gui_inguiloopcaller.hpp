/*
 *	File: decent_gui_inguiloopcaller.hpp
 *
 *	Created on: 04 Feb 2017
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef DECENT_GUI_INGUILOOPCALLER_HPP
#define DECENT_GUI_INGUILOOPCALLER_HPP

#include "ui_wallet_functions_base.hpp"
#include <QObject>

namespace decent{ namespace gui{

class InGuiLoopCaller : public QObject
{
    Q_OBJECT
public:
    InGuiLoopCaller();
    ~InGuiLoopCaller();

    void CallFunctionInGuiLoop(SetNewTask_last_args,void* owner,TypeCallbackSetNewTaskGlb fpFnc);

private:
signals:
    void NewFunctionToCallSig(SetNewTask_last_args,void* owner,TypeCallbackSetNewTaskGlb fpFnc);

private slots:
    void NextFunctionToCallSlot(SetNewTask_last_args,void* owner,TypeCallbackSetNewTaskGlb fpFnc);
};

}}

#endif // DECENT_GUI_INGUILOOPCALLER_HPP
