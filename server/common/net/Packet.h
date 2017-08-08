#ifndef __NET_SERVER__PACKET_H___
#define __NET_SERVER__PACKET_H___
#include <vector>
#include <memory>
#include <string.h>

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
	struct packet_header
	{
		uint16_t length : 14;
		uint16_t opCode;
	};

	struct packet
	{
		packet(uint16_t opcode);
		packet(uint16_t opcode, uint8_t* data, uint16_t length);
		packet(uint8_t* data, uint16_t length);

		uint16_t Opcode() const
		{
			_header.opCode;
		}

		uint32_t Length() const
		{
			return _content.size();
		}

		const uint8_t* Data() const
		{
			return _content.data() + sizeof(packet_header);
		}

		uint32_t ContentLength() const
		{
			return _content.size() - sizeof(packet_header);
		}

		const uint8_t* Content() const
		{
			return _content.data() + sizeof(packet_header);
		}

	private:
		packet_header _header;
		std::vector<uint8_t> _content;
	};
}
#endif