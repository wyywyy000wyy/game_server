#pragma once
#include <memory>
#include "common/net/net_object.h"
#include "common/net/tcp_server.h"

namespace game_common
{
	typedef int PlayerID;

	class Player
	{
	public:
		Player(PlayerID pid);
		void set_conn(game_net::tcp_client_ptr conn);
		void send_pack(game_net::PacketPtr pack);

		PlayerID get_player_id() const {
			return _player_id;
		}
	protected:
		game_net::tcp_client_ptr _conn = NULL;
		PlayerID _player_id;
	};

	typedef std::shared_ptr<Player> player_ptr;
}
