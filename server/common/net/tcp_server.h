#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__
#include "NetDef.h"
#include <asio.hpp>
#include <memory>
#include <functional>
#include <unordered_map>
#include "tcp_client.h"
#include "net_object_mgr.h"
#include "Packet.h"

namespace game_net
{
	class tcp_client;

	typedef std::shared_ptr<tcp_client> TcpClientPtr;

	typedef std::function<void(TcpClientPtr)> ConnectedCallback;

	typedef std::function<void(TcpClientPtr, int opcode, PacketPtr)> ServerReceiveCallback;
	typedef std::function<void(TcpClientPtr, int)> ServerDisconnectCallback;

	//typedef void(*ConnectedCallback)(TcpClientPtr);

	class tcp_server : public std::enable_shared_from_this<tcp_server>
	{
	public:
		tcp_server(asio::io_service& ios);
		tcp_server();

		~tcp_server();

		bool Start(int port);
		void RegisterConnectedCallback(ConnectedCallback);
		void RegisterReceiveCallback(ServerReceiveCallback);
		void RegisterDisconnectCallback(ServerDisconnectCallback);
	protected:
		void _AsyncAccept();
		void _HandleAccept(TcpClientPtr, std::error_code ec);
	private:
		ConnectedCallback m_connectedCallback;
		ServerReceiveCallback _receiveCallback;
		ServerDisconnectCallback _disconnectCallback;
		asio::io_service& m_service;
		asio::ip::tcp::socket m_socket;
		asio::ip::tcp::acceptor m_accepter;
		std::unordered_map<SessionId, TcpClientPtr> _sessionMap;
		SessionId _sessionId;
		asio::io_service* _service;
		net_object_mgr* _net_obj_mgr;
	};
}


#endif