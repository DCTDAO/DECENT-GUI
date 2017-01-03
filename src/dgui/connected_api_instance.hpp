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

typedef void (*WaletFncType)(graphene::wallet::wallet_api* wa,void*ud);
typedef void (*DoneFuncType)(void*user_data);
typedef void (*ErrFuncType)(void*user_data,const std::string& err,const std::string& details);

namespace gui_wallet
{

/*
 *  struncture that conatins all necessary pointers for api-s
 *   most probably this will be moved to the cpp file, because it is needed only by
 *   one source file
 */
struct StructApi{StructApi():wal_api(NULL),gui_api(NULL){} graphene::wallet::wallet_api* wal_api; fc::rpc::gui* gui_api;};

graphene::wallet::wallet_api* GetCurWalletApi();
fc::rpc::gui* GetCurGuiApi();
int CreateConnectedApiInstance( const graphene::wallet::wallet_data* a_wdata,
                                const std::string& a_wallet_file_name,
                                void* a_pOwner,DoneFuncType a_fpDone, ErrFuncType a_fpErr);
void UseConnectedApiInstance(WaletFncType a_fpFunction, void* a_pUserData);

}

#endif // CONNECTED_API_INSTANCE_HPP
