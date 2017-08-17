#pragma once

#include <memory>
namespace game_common
{
	class game_map;

	class game_msg_queue;
}

namespace game_net
{
	class tcp_client;
}

class pyhsics_server
{
public:
	pyhsics_server(const pyhsics_server&) = delete;
	pyhsics_server& operator=(const pyhsics_server&) = delete;
private:
	std::unique_ptr<game_common::game_map> _map;
	std::unique_ptr<game_common::game_msg_queue> _queue;
	std::unique_ptr<game_net::tcp_client> _net;
};