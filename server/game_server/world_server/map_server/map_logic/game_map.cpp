#include "game_map.h"
#include "net/msg_define.hpp"
#include <chrono>
using namespace std;

class game_map_private {
	friend game_map;
	game_map_private(game_map* out):this_(out){

	}

	int get_tile_id(game_common::VEC3 pos)
	{
		int x = pos.x;
		int y = pos.z;

		int w_num = (this_->map_width + this_->tile_width - 1) / this_->tile_width;

		int h_num = (this_->map_height + this_->tile_height - 1) / this_->tile_height;

		return h_num * this_->tile_w_num + w_num;
	}

	game_map* this_;
};

game_map::game_map():_inner(new game_map_private(this))
{
	init();
}


void game_map::init()
{
	map_width = 1000;
	map_height = 1000;

	tile_width = 100;
	tile_height = 100;

	tile_w_num = (map_width + tile_width - 1) / tile_width;
	tile_h_num = (map_height + tile_height - 1) / tile_height;

	_tile_map = new map_tile*[tile_h_num * tile_width];

	memset(_tile_map, 0, sizeof(map_tile*) * tile_h_num * tile_width);
}

int game_map::get_tile_id(const game_common::VEC3& pos)
{
	int x = pos.x;
	int y = pos.z;

	int w_num = (this->map_width + this->tile_width - 1) / this->tile_width;

	int h_num = (this->map_height + this->tile_height - 1) / this->tile_height;

	return 0;//h_num * this->tile_w_num + w_num;
}

bool game_map::has_player(game_common::PlayerID pid)
{
	if (_player_map.find(pid) != _player_map.end())
	{
		return true;
	}
	if (_objs_map.find(pid) != _objs_map.end())
	{
		return true;
	}

	return false;
}

map_tile* game_map::get_tile(int tile_id)
{
	map_tile* tile = _tile_map[tile_id];
	if (tile)
		return tile;

	tile = new map_tile(this, tile_id);
	_tile_map[tile_id] = tile;
	return tile;
}

void game_map::broad_msg(game_net::PacketPtr pk)
{
	for (auto i = _player_map.begin(); i != _player_map.end(); ++i)
	{
		auto player = i->second;
		player->send_pack(pk);
	}
}

void game_map::player_move(game_common::player_ptr player, game_net::PacketPtr pk)
{
	auto mp = _objs_map[player->get_player_id()];
	if (!mp)
		return;
	mp->set_pos(pk);
	if(mp->get_cur_tile())
	mp->get_cur_tile()->broad_msg(mp->SerializeMove());
}


void game_map::join_map(game_common::player_ptr player)
{
	if (has_player(player->get_player_id()))
	{
		return;
	}

	_player_map[player->get_player_id()] = player;

	map_player_ptr mp = make_shared<map_player>(player);

	_objs_map[player->get_player_id()] = mp;

	int tile_id = get_tile_id(mp->get_pos());

	map_tile* tile = get_tile(tile_id);

	MSG_S2C_ObjectBorn msg;
	msg.player_id_ = player->get_player_id();
	msg.type = 1;
	player->send_pack(msg.Serialize());

	tile->join_tile(mp);

	////MSG_S2C_ObjectBorn msg2;
	//msg.player_id_ = msg.player_id_ + 10000;//test
	////msg2.type = 1;
	//player->send_pack(msg.Serialize());

}

void game_map::Update(float dt)
{
	for (int i = 0; i < tile_h_num * tile_width; ++i)
	{
		map_tile* tile = _tile_map[i];
		if (tile)
		{
			tile->Update(dt);
		}
	}
}


