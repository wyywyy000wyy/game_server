#include "physics_component.h"
#include <sstream>
using namespace game_physics;
using namespace std;

std::string pyhsics_component::Debug()
{
	stringstream st;
	st << "x=" << PosX() << " y=" << PosY() << " z=" << PosZ();
	return st.str();
}