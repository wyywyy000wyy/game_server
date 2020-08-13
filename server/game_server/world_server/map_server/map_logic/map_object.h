#pragma once
#include "common/util/game_math.h"
#include <memory>
#include "common/server/player.h"
class map_tile;

class map_object
{
public:

	const game_common::VEC3& get_pos() { return pos; };
	void Update(float dt);

	int get_object_id() { return object_id; }

	void set_pos(game_net::PacketPtr pk);

	game_net::PacketPtr SerializeMove();
	game_net::PacketPtr SerializeBorn();

	map_tile* get_cur_tile() { return cur_tile; }
	void set_cur_tile(map_tile* tile) {
		cur_tile = tile;
	}
protected:
	game_common::VEC3 pos;
	game_common::VEC3 speed;
	float volocity=0;
	int object_id = 0;
	map_tile* cur_tile;
};

class map_player : public map_object
{
public:
	map_player(game_common::player_ptr);

	game_common::PlayerID get_player_id() {
		return _player->get_player_id();
	}

	void send_pack(game_net::PacketPtr pk)
	{
		_player->send_pack(pk);
	}
protected:
	game_common::player_ptr _player;
};

typedef std::shared_ptr<map_object> map_object_ptr;
typedef std::shared_ptr<map_player> map_player_ptr;
