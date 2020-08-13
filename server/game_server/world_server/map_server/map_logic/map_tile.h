#pragma once
#include <map>
#include "map_object.h"
#include <memory>
#include "common/server/player.h"
#include <unordered_map>
#include "net/Packet.h"

class game_map;

class map_tile 
{

	friend class game_map;
	map_tile(game_map*, int);

	void join_tile(map_player_ptr pobj);

	void Update(float dt);

	void broad_msg(game_net::PacketPtr pk);
private:

	std::map<game_common::PlayerID, map_player_ptr> _play_obj_map;

	game_map* _map;
	int _tile_id;


};
