#include "TcpServer.h"
#include "TcpClient.h"
#include <functional>
#include <iostream>
using namespace asio;
using namespace std;
using namespace game_net;

TcpServer::TcpServer(asio::io_service& ios):m_service(ios), m_socket(m_service), m_accepter(m_service), _sessionId(0)
{

}

TcpServer::~TcpServer()
{

}

bool TcpServer::Start(int port)
{
	if (!m_connectedCallback || m_accepter.is_open())
	{
		return false;
	}

	ip::tcp::endpoint p(ip::address::from_string("127.0.0.1"), port);
	m_accepter.open(p.protocol());
	m_accepter.set_option(ip::tcp::acceptor::reuse_address(true));
	asio::error_code ec;
	m_accepter.bind(p,ec);
	if (ec)
	{
		cerr << ec.message();
	}
	m_accepter.listen(65532, ec);
	if (ec)
	{
		cerr << ec.message();
	}
	_AsyncAccept();
	return true;
}

void TcpServer::_HandleAccept(TcpClientPtr p, std::error_code ec)
{
	if (!ec)
	{
		_sessionMap[p->Id()] = p;
		p->RegisterRecvCallback(std::bind(_receiveCallback, p, std::placeholders::_1, std::placeholders::_2));
		m_connectedCallback(p);
	}
	_AsyncAccept();
}

void TcpServer::_AsyncAccept()
{
	TcpClientPtr p = make_shared<TcpClient>(m_service,_sessionId++);
	m_accepter.async_accept(p->m_socket,
		std::bind(&TcpServer::_HandleAccept, shared_from_this(), p , std::placeholders::_1)
		);

}

void TcpServer::RegisterReceiveCallback(ServerReceiveCallback cb)
{
	//_receiveCallback = std::bind(cb, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
	_receiveCallback = cb;
}

void TcpServer::RegisterConnectedCallback(ConnectedCallback b)
{
	m_connectedCallback = b;
}
