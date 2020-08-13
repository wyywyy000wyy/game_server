#pragma once

#include <memory>
#include "server/server_base.h"
#include "common/server/player_mng.h"
#include "map_logic/game_map.h"


namespace game_net
{
	class tcp_client;
}

class map_server : public game_common::server_base
{
public:
	map_server();
	map_server(const map_server&) = delete;
	map_server& operator=(const map_server&) = delete;

	virtual void on_connect(std::shared_ptr<game_net::net_object>);

	virtual void run();


private:
	//std::unique_ptr<game_common::game_map> _map;
	//std::unique_ptr<game_common::game_msg_queue> _queue;
	game_common::player_mng* _play_mng;
	game_map* _main_map;
	asio::io_service ios;
	std::map<SessionId, game_common::player_ptr> _session_2_player_map;
	std::unique_ptr<game_net::tcp_client> _net;
};