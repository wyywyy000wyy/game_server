#pragma once
#include "NetDef.h"

namespace game_net
{
	class net_object_mgr;

	class net_object
	{
	public:
		net_object(SessionId id, net_object_mgr* mgr): _sessionId(id), _mgr(mgr){}
	//protected:
		const SessionId _sessionId;
		const net_object_mgr * const _mgr;
	};
};
