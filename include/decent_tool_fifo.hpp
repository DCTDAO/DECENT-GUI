/*
 *	File: decent_tool_fifo.hpp
 *
 *	Created on: 04 Feb 2017
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef DECENT_TOOL_FIFO_HPP
#define DECENT_TOOL_FIFO_HPP

#include <mutex>
#include <stddef.h>

namespace decent { namespace tools{

template <typename TypeInp, typename TypeTaskFnc>
struct taskListItem{
    taskListItem(TypeTaskFnc fn_tsk_dn,const TypeInp& inp,void* owner = NULL,void* clbArg=NULL);

    struct taskListItem*    next;
    void*                   owner;
    void*                   callbackArg;
    TypeInp                 input;
    TypeTaskFnc             fn_tsk_dn2;
};

template <typename TypeInp,typename TypeTaskFnc>
class FiFo
{
public:
    FiFo();
    virtual ~FiFo();

    /*
     *  return
     *      NULL     -> there is no any task to handle
     *      non NULL -> pointer to tast to fullfill
     */
    bool GetFirstTask(decent::tools::taskListItem<TypeInp,TypeTaskFnc>* firstTaskBuffer);
    void AddNewTask(const TypeInp& a_inp, void* a_owner, void* a_clbData,...);

protected:
    taskListItem<TypeInp,TypeTaskFnc>   m_InitialTaskBuffer;
    taskListItem<TypeInp,TypeTaskFnc>*  m_pFirstTask;
    taskListItem<TypeInp,TypeTaskFnc>*  m_pLastTask;
    std::mutex                          m_task_mutex;
};

}}


#include "decent_tool_fifo.tos"

#endif // DECENT_TOOL_FIFO_HPP
