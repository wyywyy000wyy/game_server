#pragma once
#include "game_event.h"
#include <vector>

class GameCondition : private GameEventListener
{
public:
	virtual bool ConditionCheck();
	virtual ~GameCondition();
	bool Achieve() const { return m_conditionAchieve; }
private:
	bool m_conditionAchieve;
	std::vector<GameEventType> m_eventList;
};