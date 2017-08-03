#ifndef _ASYNC_OPERATION_H_
#define _ASYNC_OPERATION_H_
#include <utility>
#include <stdint.h>
class AsyncQueue;

class async_operation
{
	typedef void(*func_type)(async_operation*);
public:
	void call()
	{
		func_(this);
	}
	void cancel()
	{
		func_ = emptyFunc;
	}

	static void emptyFunc(async_operation*)
	{

	}
protected:

	async_operation(func_type func) :func_(func) {}

private:
	func_type func_;
};

template<typename Handler>
class asyc_handler : public async_operation
{
public:
	asyc_handler(Handler& h) :async_operation(&asyc_handler::do_call), handler_(h) {}

	static void do_call(async_operation* p)
	{
		asyc_handler* h(static_cast<asyc_handler*>(p));

		Handler handler(std::move(h->handler_));

		handler();
	}
private:
	Handler handler_;
};
typedef uint64_t IdentityType;

template<typename Handler>
class unique_asyc_handler : public async_operation
{
public:
	
	unique_asyc_handler(Handler& h, IdentityType& id, AsyncQueue& queue) : async_operation(&unique_asyc_handler::do_call), handler_(h),id_(id),queue_(queue) {}

	static void do_call(async_operation* p)
	{
		unique_asyc_handler* h(static_cast<unique_asyc_handler*>(p));

		Handler handler(std::move(h->handler_));

		handler();

		//queue_.RemoveQunique(this, id_);
	}
private:
	AsyncQueue& queue_;
	Handler handler_;
	IdentityType id_;
};

#endif
