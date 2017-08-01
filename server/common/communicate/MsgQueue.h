#pragma once
#include "common/net/Packet.h"
#include <memory>
namespace google
{
	namespace protobuf
	{
		class Message;
	}
}

namespace zmq
{
	class socket_t;
}

namespace game_common
{
	class game_msg_queue
	{
	public:
		void PushMsg(uint16_t opCode, const google::protobuf::Message& msg);
	private:
		std::unique_ptr<zmq::socket_t> _sock;
	};
}