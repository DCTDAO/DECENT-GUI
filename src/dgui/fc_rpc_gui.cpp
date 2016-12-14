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

using namespace fc::rpc;
using namespace fc;

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
      m_semaphore(),
      m_pOwner(NULL),
      m_info_report(&default_reporter_function),
      m_warning_report(&default_reporter_function),
      m_error_report(&default_reporter_function)
{
    //
}


gui::~gui()
{
   if( _run_complete.valid() )
   {
      stop();
   }
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

void gui::run()
{
   while( !_run_complete.canceled() )
   {
      try
      {
         try
         {
            //getline( _prompt.c_str(), line );
             m_semaphore.wait();
         }
         catch ( const fc::eof_exception& /*e*/ )
         {
            break;
         }
#if 0
         std::cout << line << "\n";
         line += char(EOF);
         fc::variants args = fc::json::variants_from_string(line);;
         if( args.size() == 0 )
            continue;

         const string& method = args[0].get_string();

         auto result = receive_call( 0, method, variants( args.begin()+1,args.end() ) );
         auto itr = _result_formatters.find( method );
         if( itr == _result_formatters.end() )
         {
            std::cout << fc::json::to_pretty_string( result ) << "\n";
         }
         else
            std::cout << itr->second( result, args ) << "\n";
#endif
      }
      catch ( const fc::exception& e )
      {
         //std::cout << e.to_detail_string() << "\n";
         (*m_error_report)(m_pOwner,"%s\n",e.to_detail_string().c_str());
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
