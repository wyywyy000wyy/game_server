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
		void ReceiveMsg(google::protobuf::Message& msg);

		void SendMsg(std::shared_ptr<game_net::packet> msg);
		std::shared_ptr<game_net::packet> ReceiveMsg();
	private:
		std::unique_ptr<zmq::socket_t> _sock;
	};
}