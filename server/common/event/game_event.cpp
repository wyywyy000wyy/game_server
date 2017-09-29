#include "game_event.h"

GameEventManager::GameEventManager():GameEventListener(NULL)
{
}

GameEventManager::~GameEventManager()
{
}

GameEventListener::GameEventListener(GameEventListener* parent):m_parent(parent)
{
}

GameEventListener::~GameEventListener()
{
	while (!m_listenEventHandlers.empty())
	{
		RemoveEventHandler(m_listenEventHandlers.begin()->first);
	}
}

static void GameEventSendFunction(GameEventPtr e, void* p)
{
	if (p)
	{
		((GameEventListener*)p)->SendEvent(e);
	}
}

void GameEventListener::AddEvenHandler(GameEventType type, EventHandlerBasePtr handler)
{
	auto iter = m_listenEventHandlers.find(type);
	if (iter == m_listenEventHandlers.end() || !iter->second)
	{
		std::shared_ptr<GameEventHandlerList> list = std::make_shared<GameEventHandlerList>();
		m_listenEventHandlers[type] = list;
		if (m_parent)
		{
			m_parent->AddEvenHandler(type, GameEventSendFunction, this);
		}
	}

	m_listenEventHandlers[type]->push_back(handler);
}

void GameEventListener::RemoveEventHandler(GameEventType type)
{
	auto iter = m_listenEventHandlers.find(type);
	if (iter != m_listenEventHandlers.end())
	{
		if (m_parent)
		{
			m_parent->RemoveEventHandler(type, GameEventSendFunction,this);
		}
		m_listenEventHandlers.erase(iter);
	}
}

void GameEventListener::SendEvent(GameEventPtr e)
{
	DispatchEvent(e);
}

void GameEventListener::DispatchEvent(GameEventPtr e)
{
	auto iter = m_listenEventHandlers.find(e->type);
	if (iter != m_listenEventHandlers.end() && iter->second)
	{
		DispatchEvent(e, iter->second);
	}
}

void GameEventListener::DispatchEvent(GameEventPtr e, GameEventHandlerListPtr list)
{
	for (auto i = list->begin(); i != list->end(); ++i)
	{
		(*i)->call(e);
	}
}
