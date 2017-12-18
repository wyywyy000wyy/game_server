#include "server_base.h"

#define CONFIG_SECTION_COMMON_SERVER "server_info"
#define CONFIG_SERVER_NAME "name"

using namespace game_common;

game_common::server_base::server_base()
{

}

game_common::server_base::~server_base()
{

}

void game_common::server_base::start(const server_param& param)
{
	_init_param = param;

	__init();
	init();
	run();
}

void game_common::server_base::stop()
{
	deinit();
	_thread_ptr->join();
	delete _thread_ptr;
	_thread_ptr = nullptr;
}

void game_common::server_base::on_receive(std::shared_ptr<game_net::net_object> netObj, int opCode, game_net::PacketPtr packet)
{
	auto i = _handlers.find(opCode);
	if (i != _handlers.end())
	{
		i->second(netObj,opCode,packet);
	}
}

void game_common::server_base::register_handle(int opCode, std::function<void(std::shared_ptr<game_net::net_object>, int, game_net::PacketPtr)> handler)
{
	_handlers[opCode] = handler;
}

const std::string& game_common::server_base::name()
{
	return _server_name;
}

void game_common::server_base::__init()
{
	_config.open(_init_param.config_name);
	_server_name = _init_param.server_name;

	_sock.RegisterConnectedCallback(std::bind(&game_common::server_base::__on_connect, this, std::placeholders::_1));
	_sock.RegisterReceiveCallback(std::bind(&game_common::server_base::__on_receive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	
	_sock.RegisterDisconnectCallback([this](game_net::TcpClientPtr client, int opCpde)
	{
		on_disconnect(client->net_obj(), opCpde);
	});
	//_sock.Start(_init_param.listen_port);

	//_thread_ptr = new std::thread(&game_net::tcp_server::Start, _sock, _init_param.listen_port);
	_thread_ptr = new std::thread([this]() {
		_sock.Start(_init_param.listen_port);
	}
	);
	//_server_name = _config.get_string(CONFIG_SECTION_COMMON_SERVER, CONFIG_SERVER_NAME, "Anonymous");
}

void game_common::server_base::__on_connect(game_net::TcpClientPtr client)
{
	on_connect(client->net_obj());
}

void game_common::server_base::__on_receive(game_net::TcpClientPtr client, int opCpde, game_net::PacketPtr packet)
{
	on_receive(client->net_obj(), opCpde, packet);
}
