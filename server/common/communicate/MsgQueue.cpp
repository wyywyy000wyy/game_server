#include "MsgQueue.h"
#include "zmq.hpp"
#include "common/net/NetPackDefine.pb.h"

using namespace game_common;


void game_msg_queue::PushMsg(uint16_t opCode, const google::protobuf::Message& msg)
{
	std::string data;
	msg.SerializeToString(&data);
	_sock->send(data.c_str(),data.length());
}

