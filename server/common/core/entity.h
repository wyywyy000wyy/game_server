#pragma once
#include <memory>
#include <list>

namespace game_core
{
	class component;

	class entity : std::enable_shared_from_this<entity>
	{
	public:
		 bool AddComponent(std::shared_ptr<component> c);

		 virtual void Tick(int dt) {};

		 virtual std::string Debug();

		 void SetName(const std::string& name) { _name = name; }
	protected:
		std::string _name{ "none" };
		std::list<std::shared_ptr<component>> _component_list;
	};
}