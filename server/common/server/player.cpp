#include "player.h"
using namespace game_common;


Player::Player(PlayerID pid):_player_id(pid)
{

}

void Player::set_conn(game_net::tcp_client_ptr conn)
{
	_conn = conn;
}

void Player::send_pack(game_net::PacketPtr pack)
{
	if (_conn)
	{
		_conn->SendPacket(pack);
	}
}


