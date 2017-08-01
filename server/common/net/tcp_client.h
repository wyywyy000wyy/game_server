#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__
#include <asio.hpp>
#include "NetDef.h"
#include "Buffer.h"
#include "Packet.h"
#include <memory>
#include <functional>

namespace game_net
{
	class TcpServer;

	typedef std::function<void(int, PacketPtr)> ReceiveCallback;

	class TcpClient : public std::enable_shared_from_this<TcpClient>
	{
		friend class TcpServer;
	public:
		TcpClient(asio::io_service& ios, SessionId sessionId = 0);

		void Connect(std::string host, short port);
		void SendPacket(PacketPtr pack);
		void SendPacket(uint16_t opCode, const google::protobuf::Message& msg);
		void SendPacketNoBlock(uint16_t opCode, const google::protobuf::Message& msg); //for test client 
		void SendPacketNoBlock(PacketPtr pack); //for test client 
		void RegisterRecvCallback(ReceiveCallback c);
		void Start();
		void Stop();
		void Push();
		SessionId Id() const { return _sessionId; }
		bool HasSomethingToWrite();
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
		asio::ip::tcp::socket m_socket;
		ServerBuffer m_rBuffer;
		ServerBuffer m_wBuffer;
		PacketPtr m_packet;
		bool m_isRunning;
		volatile bool m_isWritting;
		const SessionId _sessionId;
	};

}



#endif