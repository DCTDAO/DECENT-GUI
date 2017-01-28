/*
 *	File: fc_rpc_gui.cpp
 *
 *	Created on: 14 Dec 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */

#include "fc_rpc_gui.hpp"
#include <fc/io/json.hpp>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

using namespace fc::rpc;
using namespace fc;
extern int g_nDebugApplication ;

#if 0
std::map<string,std::function<string(variant,const variants&)> > _result_formatters;
fc::future<void> _run_complete;
decent_tools::UnnamedSemaphoreLite m_semaphore;
void*                              m_pOwner;
TYPE_REPORTER                      m_info_report;
TYPE_REPORTER                      m_warning_report;
TYPE_REPORTER                      m_error_report;
#endif

static int default_reporter_function(void* owner,const char* form,...);

gui::gui()
    :
      _result_formatters(),
      m_pFirstTask(NULL),
      m_pLastTask(NULL),
      m_semaphore(),
      m_pOwner(NULL),
      m_info_report(&default_reporter_function),
      m_warning_report(&default_reporter_function),
      m_error_report(&default_reporter_function)
{
    //m_pTaskInitial = new taskList;
}


gui::~gui()
{
   taskListItem *pItemTodelete, *pItemTemp;
   if( _run_complete.valid() )
   {
      stop();
   }

   m_task_mutex.lock();
   pItemTodelete = m_pFirstTask ? m_pFirstTask->next : NULL;
   while(pItemTodelete)
   {
       pItemTemp = pItemTodelete->next;
       delete pItemTodelete;
       pItemTodelete = pItemTemp;
   }
   m_task_mutex.unlock();

   //delete m_pTaskInitial;
}


void gui::SetOwner(void* a_owner)
{
    m_pOwner = a_owner;
}


void gui::SetInfoReporter(TYPE_REPORTER a_info_reporter)
{
    m_info_report = a_info_reporter;
}


void gui::SetWarnReporter(TYPE_REPORTER a_warn_reporter)
{
    m_warning_report = a_warn_reporter;
}

void gui::SetErrorReporter(TYPE_REPORTER a_err_reporter)
{
    m_error_report = a_err_reporter;
}


variant gui::send_call( api_id_type api_id, string method_name, variants args /* = variants() */ )
{
   FC_ASSERT(false);
}

variant gui::send_callback( uint64_t callback_id, variants args /* = variants() */ )
{
   FC_ASSERT(false);
}

void gui::send_notice( uint64_t callback_id, variants args /* = variants() */ )
{
   FC_ASSERT(false);
}

void gui::start()
{
   //cli_commands() = get_method_names(0);
   _run_complete = fc::async( [&](){ run(); } );
}

void gui::stop()
{
   _run_complete.cancel();
   _run_complete.wait();
}

void gui::wait()
{
   _run_complete.wait();
}

void gui::format_result( const string& method, std::function<string(variant,const variants&)> formatter)
{
   _result_formatters[method] = formatter;
}


void gui::SetNewTask(void* a_owner,void* a_callbackArg,const std::string& a_line,TYPE_TASK_DONE2 a_fpTaskDone)
{
    SetNewTask_base(a_owner,a_callbackArg,a_line,a_fpTaskDone);
}


void gui::SetNewTask_base(void* a_pOwner,void* a_clbkArg,const std::string& a_line,...)
{
    //m_line = a_line;
    //taskListItem * pTaskNext;

    TYPE_TASK_DONE2 fpTaskDone;
    va_list aFunc;

    va_start( aFunc, a_line );  /* Initialize variable arguments. */
    fpTaskDone = va_arg( aFunc, TYPE_TASK_DONE2);
    va_end( aFunc );                /* Reset variable arguments.      */

    m_task_mutex.lock();
    if(!m_pFirstTask)
    {
        //m_InitialTaskBuffer.next = NULL;
        m_pFirstTask = m_pLastTask = &m_InitialTaskBuffer;

        m_pLastTask->next = NULL;
        m_pLastTask->owner = a_pOwner;
        m_pLastTask->callbackArg = a_clbkArg;
        m_pLastTask->line = a_line;
        m_pLastTask->fn_tsk_dn = fpTaskDone;
    }
    else
    {
        m_pLastTask->next = new taskListItem(a_pOwner,a_clbkArg,a_line,fpTaskDone);
        m_pLastTask = m_pLastTask->next;
    }
    m_task_mutex.unlock();

    m_semaphore.post();
}


bool gui::GetFirstTask(gui::taskListItem* a_pFirstTaskBuffer)
{
    bool bRet(false);
    struct taskListItem* pTmp = NULL;

    //printf("line=%d\n",__LINE__);

    m_task_mutex.lock();
    if(m_pFirstTask)
    {
        //printf("line=%d\n",__LINE__);
        memcpy(a_pFirstTaskBuffer,m_pFirstTask,sizeof(gui::taskListItem));
        if(m_pFirstTask->next)
        {
            pTmp = m_pFirstTask->next;
            memcpy(m_pFirstTask,m_pFirstTask->next,sizeof(struct taskListItem));
            delete pTmp;
        }
        else {m_pFirstTask = NULL;}
        bRet = true;
    } // if(m_pFirstTask)
    m_task_mutex.unlock();

    return bRet;
}

#include <stdio.h>

void gui::run()
{
   struct taskListItem aTaskItem;
   //int nIteration;
   int err = 0;

   while( !_run_complete.canceled() )
   {
      try
      {
         m_semaphore.wait();
         //nIteration = 0;

         while(GetFirstTask(&aTaskItem))
         {
             //printf("!!!!!!!!!!!! %d, aItem.line=%s\n",++nIteration,aTaskItem.line.c_str());
             std::string line = aTaskItem.line;
             //std::cout << line << "\n";
             line += char(EOF);
             fc::variants args = fc::json::variants_from_string(line);
             if( args.size() == 0 )continue;
             const string& method = args[0].get_string();

             //const string& method = m_method;

             auto result = receive_call( 0, method, variants( args.begin()+1,args.end() ) );
             auto itr = _result_formatters.find( method );
             if( itr == _result_formatters.end() )
             {
                //std::cout << "!!!!!!!if\n"<<fc::json::to_pretty_string( result ) << "\n";
                (*aTaskItem.fn_tsk_dn)(aTaskItem.owner,aTaskItem.callbackArg,err,aTaskItem.line, fc::json::to_pretty_string( result ));
                (*m_info_report)(m_pOwner,"%s\n",fc::json::to_pretty_string( result ).c_str());
             }
             else
             {
                //std::cout << "!!!!!!!!else\n"<<itr->second( result, args ) << "\n";
                (*aTaskItem.fn_tsk_dn)(aTaskItem.owner,aTaskItem.callbackArg,err,aTaskItem.line, itr->second( result, args ));
                (*m_info_report)(m_pOwner,"%s\n",itr->second( result, args ).c_str());
             }
         }

      }
      catch ( const fc::exception& e )
      {
         if(g_nDebugApplication){printf("file:\"" __FILE__ "\",line:%d\n",__LINE__);}
         if(g_nDebugApplication){std::cout << e.to_detail_string() << "\n";}
         (*m_error_report)(m_pOwner,"%s\n",e.to_detail_string().c_str());
      }
      catch(...)
      {
          if(g_nDebugApplication){printf("file:\"" __FILE__ "\",line:%d\n",__LINE__);}
          if(g_nDebugApplication){std::cout << "Unknown exception!\n";}
          (*m_error_report)(m_pOwner,"Unknown exception!\n");
      }
   }
}

#include <stdio.h>
#include <stdarg.h>

static int default_reporter_function(void* a_owner,const char* a_form,...)
{
    va_list args;
    int nRet(printf("owner=%p\n",a_owner));

    va_start( args, a_form );
    nRet += vprintf(a_form,args);
    va_end( args );
    return nRet;
}
