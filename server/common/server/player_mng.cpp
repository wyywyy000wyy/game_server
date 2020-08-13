#include "player_mng.h"
using namespace std;
using namespace game_common;

player_ptr player_mng::login(game_net::PacketPtr packet)
{
	player_ptr p = make_shared<Player>(_id_pool++);
	_player_map[p->get_player_id()] = p;
	return p;
}

void player_mng::logout(player_ptr player)
{
	_player_map[player->get_player_id()] = NULL;
}


player_ptr player_mng::FindPlayer(PlayerID _pid)
{
	auto i = _player_map.find(_pid);
	if (i != _player_map.end())
	{
		return i->second;
	}
	return NULL;
}