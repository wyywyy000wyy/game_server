#include "Packet.h"
#include "NetPackDefine.pb.h"
using namespace game_net;

bool ServerPacket::WriteTo(google::protobuf::Message& msg)
{
	return msg.ParseFromArray(body.data(), body.size());
}

bool ServerPacket::ReadFrom(const google::protobuf::Message& msg)
{
	header.length = msg.ByteSizeLong();
	body.resize(msg.ByteSizeLong());
	return msg.SerializeToArray(body.data(), body.size());
}
