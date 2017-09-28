#include "game_event.h"

void GameEventManager::AddEvenHandler(GameEventType type, EventHandlerBasePtr handler)
{
	auto iter = m_listenEventHandlers.find(type);
	if (iter == m_listenEventHandlers.end() || !iter->second)
	{
		m_listenEventHandlers[type] = std::make_shared<GameEventHandlerList>();
	}

	m_listenEventHandlers[type]->push_back(handler);
}

void GameEventManager::RemoveEventHandler(GameEventType type)
{
	auto iter = m_listenEventHandlers.find(type);
	if (iter != m_listenEventHandlers.end())
	{
		m_listenEventHandlers.erase(iter);
	}
}

void GameEventManager::RemoveEventHandler(GameEventType type, int tag)
{
	auto iter = m_listenEventHandlers.find(type);
	if (iter != m_listenEventHandlers.end() && iter->second)
	{
		auto list = iter->second;
		for (auto i = list->begin(); i != list->end(); ++i)
		{
			if ((*i)->tag == tag)
			{
				i = list->erase(i);
			}
		}
	}
}

void GameEventManager::SendEvent(GameEventPtr e)
{
	DispatchEvent(e);
}

void GameEventManager::DispatchEvent(GameEventPtr e)
{
	auto iter = m_listenEventHandlers.find(e->type);
	if (iter != m_listenEventHandlers.end() && iter->second)
	{
		auto list = iter->second;
		for (auto i = list->begin(); i != list->end(); ++i)
		{
			(*i)->call(e);
		}
	}
}

void GameEventListener::AddEvenHandler(GameEventType type, EventHandlerBasePtr )
{
}

void GameEventListener::RemoveEventHandler(GameEventType)
{
}

void GameEventListener::RemoveEventHandler(GameEventType, int tag)
{
}

void GameEventListener::DispatchEvent(GameEventPtr e)
{
}
