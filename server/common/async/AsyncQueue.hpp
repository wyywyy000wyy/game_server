#ifndef _ASYNC_QUEUE_H_
#define _ASYNC_QUEUE_H_
#include <queue>
#include <map>
#include <mutex>
#include <list>
#include "AsyncOperation.hpp"
#include <unordered_map>

typedef uint64_t IdentityType;

class AsyncQueue
{
public:
	AsyncQueue() = default;
	AsyncQueue(const AsyncQueue&) = delete;
	AsyncQueue(AsyncQueue&&) = delete;
	AsyncQueue& operator=(const AsyncQueue&) = delete;
	virtual ~AsyncQueue(){
		Clear();
	}
	int RunOne()
	{
		async_operation* op = NULL;
		{
			std::lock_guard<std::mutex> g(_taskQueueMutex);
			if (!taskQueue.empty())
			{
				op = taskQueue.front();
				taskQueue.pop_front();

			}
		}
		if (op)
		{
			op->call();
			delete op;
			return 1;
		}
		return 0;
	}

	int Run()
	{
		while (RunOne())
		{

		}
		return 0;
	}

	template <typename AsyncFunc>
	void Post(AsyncFunc&& handler)
	{
		async_operation* task = new asyc_handler<AsyncFunc>(handler);

		std::lock_guard<std::mutex> g(_taskQueueMutex);
		taskQueue.push_back(task);
	}

	template <typename AsyncFunc>
	void PostUnique(AsyncFunc&& handler, IdentityType id, bool forceReplace = true)
	{
		std::lock_guard<std::mutex> g(_uniqueQueueMutex);
		auto iter = uniqueQueue.find(id);
		if (iter != uniqueQueue.end() && iter->second)
		{
			if (forceReplace)
			{
				async_operation* task = new unique_asyc_handler<AsyncFunc>(handler, id, *this);
				iter->second->cancel();
				iter->second = task;
				std::lock_guard<std::mutex> tg(_taskQueueMutex);
				taskQueue.push_back(task);
			}
			return;
		}
		async_operation* task = new unique_asyc_handler<AsyncFunc>(handler, id, *this);
		std::lock_guard<std::mutex> tg(_taskQueueMutex);
		taskQueue.push_back(task);
		uniqueQueue[id] = task;
	}

	void RemoveQunique(void* func, IdentityType id)
	{
		auto i = uniqueQueue.find(id);
		if (i != uniqueQueue.end() && i->second == func)
		{
			uniqueQueue.erase(i);
		}
	}

	void Clear()
	{
		std::lock_guard<std::mutex> g(_uniqueQueueMutex);
		std::lock_guard<std::mutex> tg(_taskQueueMutex);
		uniqueQueue.clear();
		while (!taskQueue.empty())
		{
			delete taskQueue.front();
			taskQueue.pop_front();
		}
	}
private:
	typedef std::list<async_operation*> TaskQueueType;
	
	TaskQueueType taskQueue;
	std::mutex _taskQueueMutex;
#ifdef _WIN32
	std::map<IdentityType, async_operation*> uniqueQueue;
#else
	std::unordered_map<IdentityType, async_operation*> uniqueQueue;
#endif
	std::mutex _uniqueQueueMutex;
};

#endif