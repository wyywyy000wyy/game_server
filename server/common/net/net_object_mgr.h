#pragma once
#include "NetDef.h"
#include <memory>
#include <map>
namespace game_net
{
	class net_object;
	class net_object_mgr
	{
	public:
		std::shared_ptr<net_object> generate_net_object();
		
		static net_object_mgr* instance() 
		{ 
			static net_object_mgr mgr;
			return &mgr;
		};
	private:
		net_object_mgr() {};
	private:
		std::map<SessionId, std::shared_ptr<net_object>> _obj_map;
		SessionId _current = 0;
	};
}
