#pragma once
#include <atomic>
#include <queue>
#include "Packet.h"

namespace game_net
{
	template<typename T>
	class thread_safe_queue {
	public:
		thread_safe_queue(uint16_t max_size = 128) :_idx(0), _max_size(max_size), _idx_end(0)
		{
			_msg_count = 0;
			_queue = new T[max_size];
		}

		thread_safe_queue(const thread_safe_queue&) = delete;
		thread_safe_queue& operator=(const thread_safe_queue&) = delete;

		bool push(T msg)
		{
			if (_msg_count >= _max_size)
			{
				return false;
			}

			_queue[_idx_end] = msg;
			_idx_end = (_idx_end + 1) % _max_size;
			_msg_count--;
			return true;
		}

		T pop()
		{
			if (empty())
			{
				return NULL;
			}

			auto msg = _queue[_idx++];
			_msg_count++;

			return msg;

		}

		bool empty() {
			return _msg_count == 0;
		}
		bool full() {
			return _max_size <= _msg_count;
		}
	protected:
		std::atomic_uint _msg_count;
		const uint16_t _max_size;
		//std::queue<PacketPtr> _queue;
		uint16_t _idx;
		uint16_t _idx_end;
		T* _queue;
	};

	typedef thread_safe_queue<PacketPtr> msg_queue;

	//class msg_queue {
	//public:
	//	msg_queue(uint16_t max_size = 128);

	//	msg_queue(const msg_queue&) = delete;
	//	msg_queue& operator=(const msg_queue&) = delete;

	//	bool push(PacketPtr msg);
	//	PacketPtr pop();
	//	bool empty() {
	//		return _msg_count == 0;
	//	}
	//	bool full() {
	//		return _max_size <= _msg_count;
	//	}
	//protected:
	//	std::atomic_uint _msg_count;
	//	const uint16_t _max_size;
	//	//std::queue<PacketPtr> _queue;
	//	uint16_t _idx;
	//	uint16_t _idx_end;
	//	PacketPtr* _queue;
	//};
}
