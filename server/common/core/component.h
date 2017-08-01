#pragma once

namespace game_core
{
	class entity;

	class component
	{
		friend class entity;
	public:
		enum COMPONENT_TYPE
		{
			PHYSICS,
		};

		entity* GetOwner() { return _owner; }

		virtual int Type() const = 0;

		virtual std::string Debug() { return "component"; };

		component(const component&) = delete;

		component& operator =(const component&) = delete;
		
		virtual ~component() = default;
	protected:
		entity* _owner;
	};
}
