#include "map_server.h"
#include <iostream>
#include "common/net/PacketTool.hpp"
#include "common/util/game_math.h"
#include "common/net/msg_define.hpp"
#include "common/net/NetProtocol.pb.h"
//#include "HelloProto.pb.h"


using namespace std;
using namespace game_common;
map_server::map_server():_play_mng(new player_mng), _main_map(new game_map)
{

}

void map_server::run()
{
	register_handle(C2S_LOGIN, [this](std::shared_ptr<game_net::net_object> no, int, game_net::PacketPtr pk)->void {
		MSG_C2S_Login msg;
		msg.Unserialize(pk);

		auto client = _players_session_map[no->_sessionId];
		auto player = _play_mng->login(NULL);
		player->set_conn(client);

		_session_2_player_map[no->_sessionId] = player;

		MSG_S2C_Login msg2;
		msg2.username = msg.username;
		msg2.result = player->get_player_id();
		client->SendPacket(msg2.Serialize());

		_main_map->join_map(player);
	});
	register_handle(C2S_MOVE, [this](std::shared_ptr<game_net::net_object> no, int, game_net::PacketPtr pk)->void {
		//MSG_C2S_Move msg;
		//msg.Unserialize(pk);

		//auto client = _players_session_map[no->_sessionId];

		auto player = _session_2_player_map[no->_sessionId];

		_main_map->player_move(player, pk);

		//auto mp = _main_map->

		//MSG_S2C_Move msg2;
		//msg2.player_id = 1;
		//msg2.volocity = msg.volocity;
		//msg2.speed = msg.speed;
		//msg2.pos = msg.pos;
		//player->send_pack(msg2.Serialize());
	});
	

	auto cur_time = std::chrono::high_resolution_clock::now();
	while (1)
	{
		auto pre = cur_time;
		cur_time = std::chrono::high_resolution_clock::now();
		auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - pre);

		process_accept_queue();
		process_receive_queue();
		process_send_queue();

		_main_map->Update(dt.count() / 1000.f);
	}
}

map_server* G_S;

void map_server::on_connect(std::shared_ptr<game_net::net_object>)
{
	cout << "on_connect" << endl;
}


int main()
{
	S2C_Login login;
	login.set_id(1);
	login.set_code(1);

	string buf;

	login.SerializeToString(&buf);
	Msg msg;
	msg.set_type(MsgType::S2CLogin);
	msg.set_data(buf);

	//::google::protobuf::Message* msg = new ;
	//msg.ParseFromString

	//Phone t2;
	//t2.ParseFromString(buf);

	//map_server gs;
	//G_S = &gs;
	//game_common::server_param param;
	//param.server_name = "map_server";
	//param.config_name = "map_server";
	//param.listen_port =  52012;
	//G_S->start(param);
	return 0;
}