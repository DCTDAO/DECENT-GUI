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

typedef int (*TYPE_REPORTER)(void*owner,const char* form,...);

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

         void SetOwner(void* owner);
         void SetInfoReporter(TYPE_REPORTER info_reporter);
         void SetWarnReporter(TYPE_REPORTER warn_reporter);
         void SetErrorReporter(TYPE_REPORTER err_reporter);

      private:
         void run();

         std::map<string,std::function<string(variant,const variants&)> > _result_formatters;
         fc::future<void> _run_complete;
         decent_tools::UnnamedSemaphoreLite m_semaphore;
         void*                              m_pOwner;
         TYPE_REPORTER                      m_info_report;
         TYPE_REPORTER                      m_warning_report;
         TYPE_REPORTER                      m_error_report;
   };

} }

#endif // FC_RPC_GUI_HPP
