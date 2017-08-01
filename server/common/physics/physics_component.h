#pragma once
#include "core/component.h"
#include <vector>

namespace game_physics
{
	class pyhsics_component : public game_core::component
	{
	public:
		int Type() const override  { return game_core::component::PHYSICS; }

		float PosX() const {
			return _pos[0];
		}
		float PosY() const {
			return _pos[1];
		}
		float PosZ() const {
			return _pos[2];
		}

		virtual std::string Debug();
	protected:
		std::vector<float> _pos{ 0,0,0 };
	};
}