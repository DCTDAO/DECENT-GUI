/*
 *	File: connected_api_instance.hpp
 *
 *	Created on: 14 Dec 2016
 *	Created by: Davit Kalantaryan (Email: davit.kalantaryan@desy.de)
 *
 *  This file implements ...
 *
 */
#ifndef CONNECTED_API_INSTANCE_HPP
#define CONNECTED_API_INSTANCE_HPP

#include <graphene/wallet/wallet.hpp>
#include <string>
#include "fc_rpc_gui.hpp"

#ifndef __THISCALL__
#ifdef __MSC_VER
#define __THISCALL__ __thiscall
#else  // #ifdef __MSC_VER
#define __THISCALL__
#endif  // #ifdef __MSC_VER
#endif  // #ifndef __THISCALL__

/*
 *  struncture that conatins all necessary pointers for api-s
 *   most probably this will be moved to the cpp file, because it is needed only by
 *   one source file
 */

typedef unsigned long long int __ulli64;

struct StructApi{StructApi():wal_api(NULL),gui_api(NULL){} graphene::wallet::wallet_api* wal_api; fc::rpc::gui* gui_api;};

typedef void (__THISCALL__ *WaletFncType)(void*user_data,void* callbackArg,struct StructApi* pApi);
typedef void (*DoneFuncType)(void*user_data);
typedef void (*ErrFuncType)(void*user_data,const std::string& err,const std::string& details);
//SetPasswdFuncGUI
typedef void (*WarnYesOrNoFuncType)(void*owner,int answer,/*string**/void* str_ptr);

namespace gui_wallet
{

enum _API_STATE{DEFAULT_ST=0,CONNECTED_ST,_API_STATE_SIZE};

int CreateConnectedApiInstance( const graphene::wallet::wallet_data* a_wdata,
                                const std::string& a_wallet_file_name,
                                void* a_pOwner,DoneFuncType a_fpDone, ErrFuncType a_fpErr,
                                WarnYesOrNoFuncType a_fpFunc);
void UseConnectedApiInstance_base(void* a_pUserData,void* a_callbackArg,...);
void UseConnectedApiInstance(void* a_pUserData,void* a_callbackArg,WaletFncType a_fpFunction);
template <typename Type>
static void UseConnectedApiInstance(Type* a_obj_ptr,void* a_callbackArg,void (Type::*a_fpFunction)(void* callbackData,struct StructApi* pApi))
{
    UseConnectedApiInstance_base(a_obj_ptr,a_callbackArg,a_fpFunction);
}

}

#endif // CONNECTED_API_INSTANCE_HPP
