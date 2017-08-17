#include "net_object_mgr.h"
using namespace game_net;

std::shared_ptr<net_object> game_net::net_object_mgr::generate_net_object()
{
	_obj_map[_current] = std::make_shared<net_object>(_current, this);
	_current++;
	return _obj_map[_current - 1];
}
