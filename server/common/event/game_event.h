#pragma once
#include <map>
#include <list>
#include <memory>

typedef int GameEventType;

struct GameEvent
{
	GameEvent(GameEventType type = 0, void* UserData = NULL) :type(type), userData(UserData) {};
	GameEventType type;
	void* userData;
};
typedef std::shared_ptr<GameEvent> GameEventPtr;

class GameEventListener;

class EventHandlerBase
{
	typedef void(*func_type)(EventHandlerBase*, GameEventPtr);
public:
	void call(GameEventPtr e)
	{
		func_((EventHandlerBase*)this, e);
	}
	int tag;
protected:

	EventHandlerBase(func_type func) :func_(func) {}

private:
	func_type func_;
};

typedef std::shared_ptr<EventHandlerBase> EventHandlerBasePtr;

template<typename Handler>
class EventHandler : public EventHandlerBase
{
public:
	EventHandler(Handler& h) :EventHandlerBase(&EventHandler::do_call), handler_(h) {}

	static void do_call(EventHandlerBase * p, GameEventPtr e)
	{
		EventHandler* h = static_cast<EventHandler*>(p);

		Handler handler(h->handler_);

		handler(e);
	}
private:
	Handler handler_;
};

typedef std::list<EventHandlerBasePtr> GameEventHandlerList;

class iGameEventListener
{
public:
	virtual void AddEvenHandler(GameEventType, EventHandlerBasePtr) = 0;
	virtual void RemoveEventHandler(GameEventType) = 0;
	
protected:
	virtual void DispatchEvent(GameEventPtr e) = 0;
};

class GameEventListener
{
public:
	virtual void AddEvenHandler(GameEventType, EventHandlerBasePtr);
	virtual void RemoveEventHandler(GameEventType);
	void RemoveEventHandler(GameEventType, int tag);
	template<typename Handler>
	void AddEvenHandler(GameEventType type, Handler&& handler, int tag)
	{
		EventHandlerBasePtr fn = std::static_pointer_cast<EventHandlerBase>(std::make_shared<EventHandler<Handler>>(handler));
		fn->tag = tag;
		AddEvenHandler(type, fn);
	}
protected:
	virtual void DispatchEvent(GameEventPtr e);
};

class GameEventManager : public iGameEventListener
{
public:
	void AddEvenHandler(GameEventType, EventHandlerBasePtr);
	void RemoveEventHandler(GameEventType);
	void RemoveEventHandler(GameEventType, int tag);
	void SendEvent(GameEventPtr e);
	template<typename Handler>
	void AddEvenHandler(GameEventType type, Handler&& handler, int tag)
	{
		EventHandlerBasePtr fn = std::static_pointer_cast<EventHandlerBase>(std::make_shared<EventHandler<Handler>>(handler));
		fn->tag = tag;
		AddEvenHandler(type, fn);
	}

protected:
	virtual void DispatchEvent(GameEventPtr e);
private:


	std::map<GameEventType, std::shared_ptr<GameEventHandlerList>> m_listenEventHandlers;
	
};