#include "tcp_server.h"
#include "tcp_client.h"
#include <functional>
#include <iostream>
#include "net_object_mgr.h"
using namespace asio;
using namespace std;
using namespace game_net;

tcp_server::tcp_server(asio::io_service* ios):_service(ios), m_socket(*ios), m_accepter(*ios), _sessionId(0)
{
	_net_obj_mgr = net_object_mgr::instance();
}


tcp_server::~tcp_server()
{
	//if (_service)
	//{
	//	delete _service;
	//}
}

bool tcp_server::Start(int port)
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

	if (_service)
	{
		_service->run();
	}
	return true;
}

void tcp_server::_HandleAccept(TcpClientPtr p, std::error_code ec)
{
	if (!ec)
	{
		_sessionMap[p->Id()] = p;
		p->RegisterRecvCallback(std::bind(_receiveCallback, p, std::placeholders::_1, std::placeholders::_2));
		p->RegisterDisconnectCallback(std::bind(_disconnectCallback, p, std::placeholders::_1));
		m_connectedCallback(p);
		p->Start();
	}
	_AsyncAccept();
}

void tcp_server::_AsyncAccept()
{
	TcpClientPtr p = std::make_shared<tcp_client>(*_service, _net_obj_mgr->generate_net_object());

	m_accepter.async_accept(p->m_socket,
		std::bind(&tcp_server::_HandleAccept, this, p , std::placeholders::_1)
		);

}

void tcp_server::RegisterReceiveCallback(ServerReceiveCallback cb)
{
	//_receiveCallback = std::bind(cb, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
	_receiveCallback = cb;
}

void game_net::tcp_server::RegisterDisconnectCallback(ServerDisconnectCallback b)
{
	_disconnectCallback = b;
}

void tcp_server::RegisterConnectedCallback(ConnectedCallback b)
{
	m_connectedCallback = b;
}
