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
	typedef void(*func_type)(EventHandlerBase*, GameEventPtr, void*);
public:
	void call(GameEventPtr e)
	{
		func_((EventHandlerBase*)this, e, userData_);
	}
	virtual bool equal(const char const*) = 0;
protected:

	EventHandlerBase(func_type func, void* userData) :func_(func), userData_(userData){}

public:
	void* userData_;
	func_type func_;
};

typedef std::shared_ptr<EventHandlerBase> EventHandlerBasePtr;
typedef void(*EventHandlerType)(GameEventPtr, void*);

template<typename Handler>
class EventHandler : public EventHandlerBase
{
public:
	EventHandler(Handler& h, void* UserData) :EventHandlerBase(&EventHandler::do_call, UserData), handler_(h) {}

	static void do_call(EventHandlerBase * p, GameEventPtr e, void* userData)
	{
		EventHandler* h = static_cast<EventHandler*>(p);

		Handler handler(h->handler_);

		handler(e, userData);
	}
	bool equal(const char const* type)
	{
		return strcmp(type, typeid(handler_).name()) == 0;
	}
private:
	Handler handler_;
};

typedef std::list<EventHandlerBasePtr> GameEventHandlerList;
typedef std::shared_ptr<GameEventHandlerList> GameEventHandlerListPtr;

class iGameEventListener
{
public:
	virtual void SendEvent(GameEventPtr e) = 0;
protected:
	virtual void AddEvenHandler(GameEventType, EventHandlerBasePtr) = 0;
	virtual void DispatchEvent(GameEventPtr e) = 0;
};

class GameEventListener : public iGameEventListener
{
public:
	GameEventListener(GameEventListener* parent);
	~GameEventListener();
	template<typename Handler>
	void RemoveEventHandler(GameEventType type, Handler&& handler, void* userData = NULL)
	{
		auto iter = m_listenEventHandlers.find(type);
		if (iter != m_listenEventHandlers.end() && iter->second)
		{
			auto list = iter->second;
			list->remove_if([handler, userData](EventHandlerBasePtr p) ->bool { return p->userData_ == userData && p->equal(typeid(handler).name()) ; });
			if (list->empty())
			{
				RemoveEventHandler(type);
			}
		}
	}
	template<typename Handler>
	void AddEvenHandler(GameEventType type, Handler&& handler, void* userData = NULL)
	{
		EventHandlerBasePtr fn = std::static_pointer_cast<EventHandlerBase>(std::make_shared<EventHandler<Handler>>(handler, userData));
		AddEvenHandler(type, fn);
	}
	virtual void SendEvent(GameEventPtr e);
protected:
	void RemoveEventHandler(GameEventType);
	virtual void AddEvenHandler(GameEventType, EventHandlerBasePtr);
	GameEventListener* m_parent;
	virtual void DispatchEvent(GameEventPtr e);
	void DispatchEvent(GameEventPtr, GameEventHandlerListPtr);
	std::map<GameEventType, GameEventHandlerListPtr> m_listenEventHandlers;
};

class GameEventManager : public GameEventListener
{
public:
	GameEventManager();
	~GameEventManager();
	template<typename Handler>
	void AddEvenHandler(GameEventType type, Handler&& handler, void* userData = NULL)
	{
		EventHandlerBasePtr fn = std::static_pointer_cast<EventHandlerBase>(std::make_shared<EventHandler<Handler>>(handler, userData));
		GameEventListener::AddEvenHandler(type, fn);
	}
	template<typename Handler>
	void RemoveEventHandler(GameEventType type, Handler&& handler, void* userData = NULL)
	{
		auto iter = m_listenEventHandlers.find(type);
		if (iter != m_listenEventHandlers.end() && iter->second)
		{
			auto list = iter->second;
			list->remove_if([handler, userData](EventHandlerBasePtr p) ->bool
			{ 
				return p->userData_ == userData && p->equal(typeid(handler).name());
			});
			if (list->empty())
			{
				GameEventListener::RemoveEventHandler(type);
			}
		}
	}
};