/*
 *	File: fc_rpc_gui.hpp
 *
 *	Created on: 14 Dec 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef FC_RPC_GUI_HPP
#define FC_RPC_GUI_HPP

#include <fc/rpc/api_connection.hpp>
#include <unnamedsemaphorelite.hpp>
#include <mutex>

#ifndef __THISCALL__
#ifdef __MSC_VER
#define __THISCALL__ __thiscall
#else  // #ifdef __MSC_VER
#define __THISCALL__
#endif  // #ifdef __MSC_VER
#endif  // #ifndef __THISCALL__

//typedef void (__THISCALL__ *WaletFncType)(void*user_data,struct StructApi* pApi);
typedef int (*TYPE_REPORTER)(void*owner,const char* form,...);
typedef void (__THISCALL__ *TYPE_TASK_DONE2)(void*owner,void*arg,int err,const std::string& a_task, const std::string& task_result);

namespace fc { namespace rpc {

   /**
    *  Provides a simple wrapper for RPC calls to a given interface.
    */
   class gui : public api_connection
   {
      public:
         gui();
         virtual ~gui();

         virtual variant send_call( api_id_type api_id, string method_name, variants args = variants() );
         virtual variant send_callback( uint64_t callback_id, variants args = variants() );
         virtual void    send_notice( uint64_t callback_id, variants args = variants() );

         void start();
         void stop();
         void wait();
         void format_result( const string& method, std::function<string(variant,const variants&)> formatter);

         void SetNewTask(void* owner,void* callbackArg,const std::string& line,TYPE_TASK_DONE2 fpTaskDone);

         // void TaskDoneSlot(void*arg,int err,std::string task, std::string result);
         template <typename Type>
         void SetNewTask(Type* a_obj_ptr,void* a_callbackArg,const std::string& a_line,
                                void (Type::*a_fpFunction)(void*arg,int err,const std::string& task, const std::string& task_result))
         {
             SetNewTask_base(a_obj_ptr,a_callbackArg,a_line,a_fpFunction);
         }

         void SetOwner(void* owner);
         void SetInfoReporter(TYPE_REPORTER info_reporter);
         void SetWarnReporter(TYPE_REPORTER warn_reporter);
         void SetErrorReporter(TYPE_REPORTER err_reporter);


      private:
         void SetNewTask_base(void* owner,void* callbackArg,const std::string& line,...);
         static void default_task_done(void*,void*,int,const std::string&,const std::string&){}
         void run();
         /*
          *  return
          *      NULL     -> there is no any task to handle
          *      non NULL -> pointer to tast to fullfill
          */
         //struct taskListItem* GetFirstTask();

         std::map<string,std::function<string(variant,const variants&)> > _result_formatters;
         fc::future<void> _run_complete;

         /*typedef*/ struct taskListItem{
             taskListItem(void* a_owner = NULL,void* a_clbArg=NULL,const std::string& a_str="",
                          TYPE_TASK_DONE2 a_fn_tsk_dn=default_task_done)
                 :next(NULL),owner(a_owner),callbackArg(a_clbArg),line(a_str),fn_tsk_dn(a_fn_tsk_dn){}
             struct taskListItem* next;
             void*  owner;
             void*  callbackArg;
             std::string line;
             TYPE_TASK_DONE2 fn_tsk_dn;
         }/*taskListItem*/;
         bool GetFirstTask(gui::taskListItem* firstTaskBuffer);

         taskListItem                       m_InitialTaskBuffer;
         taskListItem*                      m_pFirstTask;
         taskListItem*                      m_pLastTask;
         std::mutex                         m_task_mutex;

         //std::string                        m_method;
         //std::string                        m_line;
         decent_tools::UnnamedSemaphoreLite m_semaphore;
         void*                              m_pOwner;
         TYPE_REPORTER                      m_info_report;
         TYPE_REPORTER                      m_warning_report;
         TYPE_REPORTER                      m_error_report;
   };

} }

#endif // FC_RPC_GUI_HPP
