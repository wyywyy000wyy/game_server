#include "game_map.h"

using namespace game_common;

void game_map::Tick(int dt)
{
	for (auto& i : _entities)
	{
		i->Tick(dt);
	}
}

void game_map::AddEntity(std::shared_ptr<game_core::entity> ep)
{
	_entities.push_back(ep);
}


