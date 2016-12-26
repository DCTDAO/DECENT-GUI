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

namespace gui_wallet
{

int CreateConnectedApiInstance( graphene::wallet::wallet_data* a_wdata,
                                const std::string& a_wallet_file_name,
                                graphene::wallet::wallet_api** a_ppApi,
                                fc::rpc::gui** a_ppGuiApi,
                                void* a_pOwner);
void UseConnectedApiInstance(WaletFncType a_fpFunction, void* a_pUserData);

}

#endif // CONNECTED_API_INSTANCE_HPP
