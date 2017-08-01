#pragma once
#include "common/core/entity.h"
#include <list>
#include <memory>


namespace game_common
{
	class game_map : public game_core::entity
	{
	public:
		void Tick(int dt);

		void AddEntity(std::shared_ptr<game_core::entity> ep);
	protected:
		std::list<std::shared_ptr<game_core::entity>> _entities;
	};
}