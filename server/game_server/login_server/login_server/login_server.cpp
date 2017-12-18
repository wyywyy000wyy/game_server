#include "login_server.h"

void login_server::init()
{
	//register_handle();
}

void login_server::on_disconnect(std::shared_ptr<game_net::net_object>, int opCode)
{

}

void login_server::on_receive(std::shared_ptr<game_net::net_object>, int opCode, game_net::PacketPtr)
{

}

void login_server::run()
{
	
}

int main()
{
	return 0;
}
