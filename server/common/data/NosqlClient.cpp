#include "NosqlClient.h"
#include <cpp_redis/redis_client.hpp>
#include <iostream>

NosqlClient::NosqlClient():m_client(new cpp_redis::redis_client)
{

}

NosqlClient::~NosqlClient()
{
}


void NosqlClient::Get(std::string key, GetStringFunc::func f)
{
	GetStringFunc* callBack = new GetStringFunc(f);

	m_client->get(key,[callBack](cpp_redis::reply& reply)
	{
		if (reply.is_string())
		{
			callBack->call(reply.as_string());
		}
		delete callBack;
	});

	//m_client->sync_commit();
}

void NosqlClient::Set(const std::string& key, const std::string& value)
{
	m_client->set(key, value, [](cpp_redis::reply& reply)
	{
		if (reply.is_error())
		{
			std::cerr << reply.error() << std::endl;
		}
	}
	);
}

void NosqlClient::Update(int dt)
{
	//m_client->sync();
	m_client->sync_commit();
}

void NosqlClient::Connect(int port)
{
	Connect("127.0.0.1", port);
}

void NosqlClient::Connect(std::string host, int port)
{
	//NosqlClientPtr p = shared_from_this();
	m_client->connect(host, port,[](cpp_redis::redis_client&)
	{
		std::cout << "fuck" << std::endl;
	}
	);
}