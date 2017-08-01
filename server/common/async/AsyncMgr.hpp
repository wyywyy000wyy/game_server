#ifndef _ASYNC_MGR_H_
#define _ASYNC_MGR_H_
#include <queue>
#include <unordered_map>
#include "AsyncOperation.hpp"

class AsyncMgr
{
public:
	int RunOne()
	{
		if (!taskQueue.empty())
		{
			async_operation* op = taskQueue.front();
			taskQueue.pop();
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

		taskQueue.push(task);
	}

	template <typename AsyncFunc>
	void PostUnique(AsyncFunc&& handler, IdentityType id, bool forceReplace = true)
	{
		auto iter = uniqueQueue.find()
		if (iter != uniqueQueue.end() )
		{
			if (forceReplace)
			{
				iter->second->asign(handler);
			}
			return;
		}
		async_operation* task = new asyc_handler<AsyncFunc>(handler);
		taskQueue.push(task);
	}
private:
	std::queue<async_operation*> taskQueue;
	std::unordered_map<IdentityType, async_operation*> uniqueQueue;
};

#endif