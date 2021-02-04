#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__
#include <asio.hpp>
#include "NetDef.h"
#include "Buffer.h"
#include "Packet.h"
#include "net_object.h"
#include <memory>
#include <functional>
#include "msg_queue.h"

namespace game_net
{
	class tcp_server;

	typedef std::function<void(int, PacketPtr)> ReceiveCallback;
	typedef std::function<void(int)> DisconnectCallback;

	class tcp_client : public std::enable_shared_from_this<tcp_client>
	{
		friend class tcp_server;
	public:
		tcp_client(asio::io_service& ios, std::shared_ptr<net_object> _obj);

		void Connect(std::string host, short port);
		void SendPacket(PacketPtr pack);
		//void SendPacket(uint16_t opCode, const google::protobuf::Message& msg);
		void SendPacketNoBlock(PacketPtr pack); //for test client 
		void RegisterRecvCallback(ReceiveCallback c);
		void RegisterDisconnectCallback(DisconnectCallback c);
		void Start();
		void Stop();
		void Push();
		void HandleMsg();
		void* UserData() { return _user_data; };
		void SetUserData(void* data) { _user_data = data; }
		SessionId Id() const { return _net_object->_sessionId; }
		bool HasSomethingToWrite();
		std::shared_ptr<net_object> net_obj() { return _net_object; };

	protected:
		void _ReadHeader();
		void _ReadBody();
		void _HandleWrite(std::error_code ec, size_t byteRead);
		void _HandleReadHeader(std::error_code ec, size_t byteRead);
		void _HandleReadBody(std::error_code ec, size_t byteRead);
		void _HandleReadData();
		void _ReadData();
	private:
		ReceiveCallback m_recvCallback;
		DisconnectCallback _disconnect_callback;
		asio::ip::tcp::socket m_socket;
		ServerBuffer m_rBuffer;
		ServerBuffer m_wBuffer;
		PacketPtr m_packet;
		bool m_isRunning;
		volatile bool m_isWritting;
		std::shared_ptr<net_object> _net_object;
		void* _user_data = NULL;
		msg_queue _msg_queue;
	};

	typedef std::shared_ptr<tcp_client> tcp_client_ptr;
}



#endif