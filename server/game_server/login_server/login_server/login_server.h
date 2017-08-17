#pragma once
#include "common/server/server_base.h"
class login_server : public game_common::server_base
{
public:
	
	virtual void on_disconnect(std::shared_ptr<game_net::net_object>, int opCode);

	virtual void on_receive(std::shared_ptr<game_net::net_object>, int opCode, game_net::PacketPtr);

	void run();

};