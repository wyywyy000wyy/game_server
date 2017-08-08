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

packet::packet(uint16_t opcode)
{
	_header.opCode = opcode;
	_header.length = 0;
	_content.resize(sizeof(_header));
#if USING_BIG_ENDIAN

#else
	memcpy(_content.data(), &_header, sizeof(_header));
#endif
}
packet::packet(uint16_t opcode, uint8_t* data, uint16_t length)
{
	_header.opCode = opcode;
	_header.length = length;
	_content.resize(sizeof(_header) + length);
#if USING_BIG_ENDIAN
#else
	memcpy(_content.data(), &_header, sizeof(_header));
#endif
	memcpy(_content.data() + sizeof(_header), data, length);
}

packet::packet(uint8_t* data, uint16_t length)
{

}
