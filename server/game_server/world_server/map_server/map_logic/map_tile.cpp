#include "map_tile.h"
#include "net/msg_define.hpp"

#define FOR_EACH_PLAYER_BEGIN() for (auto i = _play_obj_map.begin(); i != _play_obj_map.end(); ++i)\
	{\
	auto player = i->second;

#define FOR_EACH_PLAYER_END() }

map_tile::map_tile(game_map* map, int tile_id):_map(map),_tile_id(tile_id)
{

}

void map_tile::join_tile(map_player_ptr pobj)
{
	_play_obj_map[pobj->get_player_id()] = pobj;
	pobj->set_cur_tile(this);

	MSG_S2C_ObjectBorn msg;
	msg.player_id_ = pobj->get_player_id();
	msg.type = 1;
	auto pk = msg.Serialize();

	FOR_EACH_PLAYER_BEGIN()
		if (player->get_player_id() != pobj->get_player_id())
		{
			pobj->send_pack(player->SerializeBorn());
			player->send_pack(pk);
		}
		pobj->send_pack(player->SerializeMove());
	FOR_EACH_PLAYER_END()
}

void map_tile::Update(float dt)
{
	FOR_EACH_PLAYER_BEGIN()
		player->Update(dt);
	FOR_EACH_PLAYER_END()
}

void map_tile::broad_msg(game_net::PacketPtr pk)
{
	FOR_EACH_PLAYER_BEGIN()
		player->send_pack(pk);
	FOR_EACH_PLAYER_END()
}