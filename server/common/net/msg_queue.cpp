#include "msg_queue.h"
using namespace std;
using namespace game_net;

//msg_queue::msg_queue(uint16_t max_size):_idx(0),_max_size(max_size), _idx_end(0)
//{
//	_msg_count = 0;
//	_queue = new PacketPtr[max_size];
//}
//
//bool msg_queue::push(PacketPtr msg)
//{
//	if (_msg_count >= _max_size)
//	{
//		return false;
//	}
//
//	_queue[_idx_end] = msg;
//	_idx_end = (_idx_end + 1) % _max_size;
//	_msg_count--;
//	return true;
//}
//
//
//PacketPtr msg_queue::pop()
//{
//	if (empty())
//	{
//		return NULL;
//	}
//
//	auto msg = _queue[_idx++];
//	_msg_count++;
//
//	return msg;
//
//}