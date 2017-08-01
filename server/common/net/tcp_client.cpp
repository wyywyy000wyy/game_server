#include "TcpClient.h"
#include <google/protobuf/descriptor.pb.h>
#include <functional>
#include <iostream>
using namespace game_net;
using namespace asio;
TcpClient::TcpClient(io_service& ios, SessionId sessionId):m_socket(ios), m_isRunning(false),_sessionId(sessionId), m_isWritting(false)
{

}

void TcpClient::Connect(std::string host, short port)
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

void TcpClient::SendPacketNoBlock(PacketPtr p)
{
	m_socket.write_some(buffer(&p->header, sizeof(p->header)));
	m_socket.write_some(buffer(p->body.data(), p->header.length));
}

void TcpClient::SendPacketNoBlock(uint16_t opCode, const google::protobuf::Message& msg)
{
	auto packet = std::make_shared<ServerPacket>(opCode);
	packet->ReadFrom(msg);
	SendPacketNoBlock(packet);
}

void TcpClient::Start()
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

void TcpClient::Stop()
{
	m_isRunning = false;
}

void TcpClient::SendPacket(PacketPtr pack)
{
	m_wBuffer.WriteFrom(pack);
}

void TcpClient::SendPacket(uint16_t opCode, const google::protobuf::Message& msg)
{
	auto packet = std::make_shared<ServerPacket>(opCode);
	packet->ReadFrom(msg);
	SendPacket(packet);
}

void TcpClient::Push()
{
	if (!HasSomethingToWrite())
	{
		return;
	}
	m_socket.async_send(buffer(m_wBuffer.Data(), m_wBuffer.DataLength()), std::bind(&TcpClient::_HandleWrite, shared_from_this(),std::placeholders::_1,std::placeholders::_2));
	m_wBuffer.swapInOut();
}

void TcpClient::RegisterRecvCallback(ReceiveCallback c)
{
	m_recvCallback = c;
}

void TcpClient::_HandleWrite(std::error_code ec, size_t byteRead)
{
	if (ec)
	{
		std::cerr << ec.message() << std::endl;
		return;
	}
	Push();
}

bool TcpClient::HasSomethingToWrite()
{
	return m_wBuffer.DataLength() > 0;
}

void TcpClient::_ReadHeader()
{
	if (!m_isRunning)
	{
		return;
	}
	auto p = shared_from_this();

	m_packet = std::make_shared<ServerPacket>();
	asio::async_read(m_socket, buffer(&m_packet->header, sizeof(m_packet->header)), std::bind(&TcpClient::_HandleReadHeader, this,std::placeholders::_1, std::placeholders::_2));
}

void TcpClient::_HandleReadHeader(std::error_code ec,size_t byteRead)
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
void TcpClient::_HandleReadBody(std::error_code ec, size_t byteRead)
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

void TcpClient::_ReadBody()
{
	if (!m_isRunning)
	{
		return;
	}
	m_packet->body.resize(m_packet->header.length);
	asio::async_read(m_socket, buffer(m_packet->body.data(), m_packet->header.length), std::bind(&TcpClient::_HandleReadBody, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void TcpClient::_HandleReadData()
{

}

void TcpClient::_ReadData()
{
	//m_socket.async
}