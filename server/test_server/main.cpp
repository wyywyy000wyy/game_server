
#include "net/tcp_server.h"
#include <iostream>
using namespace game_net;
using namespace std;

int main()
{
	asio::io_service ios;
	
	std::shared_ptr<game_net::tcp_server> sp = make_shared<game_net::tcp_server>(ios);

	sp->RegisterConnectedCallback([](TcpClientPtr c)->void
	{
		cout << c->Id() << " connect" << endl;
		c->Start();
	});

	sp->RegisterDisconnectCallback([](TcpClientPtr c,int i)->void
	{
		cout << c->Id() << " disconnect" << endl;
	});

	sp->RegisterReceiveCallback([](TcpClientPtr c, int opCode, PacketPtr p)->void
	{
	});

	sp->Start(9998);

	ios.run();
	return 0;
}