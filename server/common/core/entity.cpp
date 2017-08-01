#include "entity.h"
#include "component.h"
#include <sstream>
using namespace game_core;
using namespace std;

bool entity::AddComponent(std::shared_ptr<component> c)
{
	for (auto i : _component_list)
	{
		if (i->Type() == c->Type())
		{
			return false;
		}
	}
	c->_owner = this;
	_component_list.push_back(c);
	return true;
}

std::string entity::Debug()
{
	stringstream st;

	st << _name << ": ";

	for (auto& i : _component_list)
	{
		st <<" -* " << i->Debug() << " *-";
	}

	st << endl;

	return st.str();
}