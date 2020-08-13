#pragma once
#include <unordered_map>
#include "player.h"
#include "common/net/Packet.h"

namespace game_common
{
	class player_mng
	{
	public:
		player_ptr login(game_net::PacketPtr packet);

		void logout(player_ptr player);

		player_ptr FindPlayer(PlayerID _pid);

	protected:
		PlayerID _id_pool = 0;
		std::unordered_map<PlayerID, player_ptr> _player_map;
	};
}