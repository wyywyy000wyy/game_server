#ifndef __NET_SERVER__PACKET_H___
#define __NET_SERVER__PACKET_H___
#include <vector>
#include <memory>
#include <cstdlib>

namespace google
{
	namespace protobuf
	{
		class Message;
	}
}

namespace game_net
{

	struct PacketHeader
	{
		uint16_t length : 14;
		uint16_t opCode;
	};

	struct ServerPacket
	{
	public:
		ServerPacket(uint16_t opCode, uint8_t* data, uint16_t length)
		{
			header.opCode = opCode;
			header.length = length;
			body.resize(length);
			memcpy(body.data(), data, length);
		}

		ServerPacket(uint16_t opCode = 0)
		{
			header.opCode = opCode;
			header.length = 0;
		}

		int PacketSize() const
		{
			return sizeof(PacketHeader) + body.size();
		}

		void WriteTo(uint8_t* data, uint16_t length)
		{
			if (length < PacketSize())
			{
				return;
			}
			memcpy(data, &header, sizeof(PacketHeader));
			memcpy(data + sizeof(PacketHeader), body.data(), body.size());
		}

		bool WriteTo(google::protobuf::Message& msg);
		bool ReadFrom(const google::protobuf::Message& msg);

		~ServerPacket()
		{

		}
		PacketHeader header;
		std::vector<uint8_t> body;
	};

	typedef std::shared_ptr<ServerPacket> PacketPtr;
}
#endif