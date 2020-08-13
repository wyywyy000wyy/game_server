#include "MsgQueue.h"
#include "zmq.hpp"
#include "common/net/NetPackDefine.pb.h"
#include "common/net/Packet.h"

using namespace game_common;

//void game_msg_queue::PushMsg(uint16_t opCode, const google::protobuf::Message& msg)
//{
//	
//}
//
//void game_msg_queue::ReceiveMsg(google::protobuf::Message& msg)
//{
//
//}
//
//void game_msg_queue::SendMsg(std::shared_ptr<game_net::packet> msg)
//{
//	_sock->send(msg->Data(), msg->Length());
//}
//
//std::shared_ptr<game_net::packet> game_msg_queue::ReceiveMsg()
//{
//	zmq::message_t m;
//	_sock->recv(&m);
//	return std::make_shared<game_net::packet>((uint8_t*)m.data(),m.size());
//}
