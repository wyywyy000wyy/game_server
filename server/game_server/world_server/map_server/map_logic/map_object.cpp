#include "map_object.h"
#include "net/msg_define.hpp"

void map_object::Update(float dt)
{
	if(volocity > 0)
		pos = pos + pos * dt * volocity;
}

map_player::map_player(game_common::player_ptr p):_player(p)
{
	object_id = p->get_player_id();
}

game_net::PacketPtr map_object::SerializeBorn()
{
	MSG_S2C_ObjectBorn born;
	born.player_id_ = get_object_id();
	born.type = 1;
	return born.Serialize();
}

game_net::PacketPtr map_object::SerializeMove()
{
	MSG_S2C_Move move;
	move.player_id = get_object_id();
	move.pos = pos;
	move.speed = speed;
	move.volocity = volocity;
	return move.Serialize();
}

void map_object::set_pos(game_net::PacketPtr pk)
{
	MSG_C2S_Move msg;
	msg.Unserialize(pk);

	pos = msg.pos;
	speed = msg.speed;
	volocity = msg.volocity;

	
}