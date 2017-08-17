#include "tcp_client.h"
#include <google/protobuf/descriptor.pb.h>
#include <functional>
#include <iostream>
using namespace game_net;
using namespace asio;
tcp_client::tcp_client(io_service& ios, std::shared_ptr<net_object> _obj):m_socket(ios), m_isRunning(false), _net_object(_obj), m_isWritting(false)
{

}

void tcp_client::Connect(std::string host, short port)
{
	ip::tcp::endpoint ep(ip::address::from_string(host), port);
	m_socket.open(ip::tcp::v4());
	error_code e;
	m_socket.set_option(ip::tcp::no_delay(true));
	m_socket.connect(ep,e);
	if (e)
	{
		std::cerr << e.message() << std::endl;
	}
}

void tcp_client::SendPacketNoBlock(PacketPtr p)
{
	m_socket.write_some(buffer(&p->header, sizeof(p->header)));
	m_socket.write_some(buffer(p->body.data(), p->header.length));
}

void tcp_client::SendPacketNoBlock(uint16_t opCode, const google::protobuf::Message& msg)
{
	auto packet = std::make_shared<ServerPacket>(opCode);
	packet->ReadFrom(msg);
	SendPacketNoBlock(packet);
}

void tcp_client::Start()
{
	if (m_isRunning)
	{
		return;
	}
	m_isRunning = true;
	if (m_packet && m_packet->header.length > 0)
	{
		_ReadBody();
	}
	else
	{
		_ReadHeader();
	}
}

void tcp_client::Stop()
{
	m_isRunning = false;
}

void tcp_client::SendPacket(PacketPtr pack)
{
	m_wBuffer.WriteFrom(pack);
}

void tcp_client::SendPacket(uint16_t opCode, const google::protobuf::Message& msg)
{
	auto packet = std::make_shared<ServerPacket>(opCode);
	packet->ReadFrom(msg);
	SendPacket(packet);
}

void tcp_client::Push()
{
	if (!HasSomethingToWrite())
	{
		return;
	}
	m_socket.async_send(buffer(m_wBuffer.Data(), m_wBuffer.DataLength()), std::bind(&tcp_client::_HandleWrite, shared_from_this(),std::placeholders::_1,std::placeholders::_2));
	m_wBuffer.swapInOut();
}

void tcp_client::RegisterRecvCallback(ReceiveCallback c)
{
	m_recvCallback = c;
}

void tcp_client::_HandleWrite(std::error_code ec, size_t byteRead)
{
	if (ec)
	{
		std::cerr << ec.message() << std::endl;
		return;
	}
	Push();
}

bool tcp_client::HasSomethingToWrite()
{
	return m_wBuffer.DataLength() > 0;
}

void tcp_client::_ReadHeader()
{
	if (!m_isRunning)
	{
		return;
	}
	auto p = shared_from_this();

	m_packet = std::make_shared<ServerPacket>();
	asio::async_read(m_socket, buffer(&m_packet->header, sizeof(m_packet->header)), std::bind(&tcp_client::_HandleReadHeader, this,std::placeholders::_1, std::placeholders::_2));
}

void tcp_client::_HandleReadHeader(std::error_code ec,size_t byteRead)
{
	if (!ec && byteRead == sizeof(m_packet->header))
	{
		if (m_packet->header.length > 0)
		{
			_ReadBody();
		}
		else
		{
			if (m_recvCallback)
			{
				auto p = m_packet;

				m_recvCallback(p->header.opCode, p);
				_ReadHeader();
			}
		}
	}
	else if(ec)
	{
		std::cerr << ec.message().c_str() << std::endl;
		////
	}
}
void tcp_client::_HandleReadBody(std::error_code ec, size_t byteRead)
{
	if (!ec && byteRead == m_packet->header.length)
	{
		if (m_recvCallback)
		{
			m_recvCallback(m_packet->header.opCode, m_packet);
			_ReadHeader();
		}
	}
	else if (ec)
	{
		std::cerr << ec.message().c_str() << std::endl;
		m_packet.reset();
	}
}

void tcp_client::_ReadBody()
{
	if (!m_isRunning)
	{
		return;
	}
	m_packet->body.resize(m_packet->header.length);
	asio::async_read(m_socket, buffer(m_packet->body.data(), m_packet->header.length), std::bind(&tcp_client::_HandleReadBody, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void tcp_client::_HandleReadData()
{

}

void tcp_client::_ReadData()
{
	//m_socket.async
}