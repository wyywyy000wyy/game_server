#pragma once
#include <string>
#include <vector>
#include <thread>
#include <map>
#include "common/net/tcp_server.h"
#include "common/net/net_object.h"

#include "common/core/config.h"
namespace game_common
{
	struct server_param
	{
		std::string server_name;
		std::string config_name;
		uint16_t listen_port;
	};

	class server_base
	{
	public:

		server_base();
		virtual ~server_base() {}

		void start(const server_param& param);

		void stop();

		virtual void run() = 0;

		virtual void init() {};

		virtual void deinit() {};

		virtual void on_connect(std::shared_ptr<game_net::net_object>) {};

		virtual void on_disconnect(std::shared_ptr<game_net::net_object>, int opCode) {};

		virtual void on_receive(std::shared_ptr<game_net::net_object>, int opCode, game_net::PacketPtr);

		void register_handle(int opCode, std::function<void(std::shared_ptr<game_net::net_object>, int, game_net::PacketPtr)>);

		const std::string&	name();
	private:
		void __init();
		void __on_connect(game_net::TcpClientPtr client);
		void __on_receive(game_net::TcpClientPtr client,int , game_net::PacketPtr);
	protected:
		server_param _init_param;
		std::string _server_name;
		config _config;
		game_net::tcp_server _sock;
		std::thread* _thread_ptr = nullptr;
		std::map<int, std::function<void(std::shared_ptr<game_net::net_object>, int, game_net::PacketPtr)>> _handlers;
		std::map<SessionId, std::shared_ptr<game_net::net_object>> _net_obj_map;
	};
}

