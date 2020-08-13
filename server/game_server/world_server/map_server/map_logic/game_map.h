#pragma once
#include <map>
#include "map_object.h"
#include <memory>
#include "common/server/player.h"
#include <unordered_map>

#include "map_tile.h"

class game_map_private;

class game_map
{
public:
	game_map();

	void Update(float dt);

	void init();

	void join_map(game_common::player_ptr player);

	void leave_map(game_common::player_ptr player);

	int get_tile_id(const game_common::VEC3& pos);

	map_tile* get_tile(int tile_id);

	bool has_player(game_common::PlayerID);

	void broad_msg(game_net::PacketPtr pk);

	void player_move(game_common::player_ptr, game_net::PacketPtr pk);
protected:

	std::string map_name;
	int map_width;
	int map_height;
	int tile_width;
	int tile_height;

	int tile_w_num;
	int tile_h_num;

	map_tile** _tile_map;
	std::unordered_map<game_common::PlayerID, game_common::player_ptr> _player_map;
	std::unordered_map<game_common::PlayerID, map_object_ptr> _objs_map;

	friend class game_map_private;
	game_map_private* _inner;
};