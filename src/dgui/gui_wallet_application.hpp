/*
 *	File: gui_wallet_application.hpp
 *
 *	Created on: 14 Dec 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file is header file for class application
 *  this class will implement functional part necessary for the application
 *
 */
#ifndef GUI_WALLET_APPLICATION_HPP
#define GUI_WALLET_APPLICATION_HPP

#include <QApplication>
#include "fc_rpc_gui.hpp"


namespace gui_wallet
{

class application : public QApplication
{
public:
    application(int& argc, char** argv);
    virtual ~application();

private:
    fc::rpc::gui    m_gui_app;
};

}

class WarnerWidget : public QObject
{
    Q_OBJECT

public:
    class QWidget*                      m_pParent2;
    int                                 m_nRes;
    decent_tools::UnnamedSemaphoreLite  m_sema;
public:
    void EmitWarningText(const QString& a_str);

public slots:
    void MakeWarningSlot(const QString& a_str);

private:
signals:
    void MakeWarningSig(const QString& a_str);
};


#endif // GUI_WALLET_APPLICATION_HPP
