#include "net/tcp_client.h"
#include "net/NetPackDefine.pb.h"
#include "net/Packet.h"
#include <iostream>
using namespace std;
using namespace asio;
using namespace game_net;

struct GameNet
{
public:
	GameNet() :_c() {
		_c = std::make_shared<tcp_client>(_ios);
	}

	void Connect(std::string host, short port)
	{
		_c->Connect(host, port);
	}

	void SendPacket(uint16_t opCode, const google::protobuf::Message& msg)
	{
		_c->SendPacketNoBlock(opCode, msg);
	}

	void ProcessInputPacket()
	{
		_c->Start();
		_ios.poll();
	}

	void RegisterRecvCallback(ReceiveCallback c)
	{
		_c->RegisterRecvCallback(c);
	}

	asio::io_service _ios;
	std::shared_ptr<tcp_client> _c;
};

int main()
{
	GameNet net;

	net.Connect("127.0.0.1", 8899);

	net.RegisterRecvCallback([](int op, PacketPtr p)
	{
		cout << "op " << op << endl;
		switch (op)
		{
		case OpCode::LS2C_LOGIN_RSP:
		{
			LS2C_LoginRsp msg;
			p->WriteTo(msg);
			cout << msg.user_name() << ":" << msg.passwd() << endl;
			break;
		}
		default:
			break;
		}
	});

	int i = 0;
	try
	{

		while (true)
		{
			C2LS_Login msg;
			msg.set_user_name("hehe");
			msg.set_passwd("yuyu");
			net.SendPacket(OpCode::C2LS_LOGIN, msg);
			net.ProcessInputPacket();

			//Sleep(500);
		}
		
	}
	catch (asio::error_code id)
	{
		cerr << id.message() << endl;
	}
	catch (...)
	{

	}
}