#pragma once
#include "net/Packet.h"
namespace game_common
{
	template <typename T>
	struct vector3
	{
		T x = 0;
		T y = 0;
		T z = 0;
		void serialize(game_net::PacketPtr packet)
		{
			packet->Write(x);
			packet->Write(y);
			packet->Write(z);
		}
		void unserialize(game_net::PacketPtr packet)
		{
			packet->Read(x);
			packet->Read(y);
			packet->Read(z);
		}

		vector3<T> operator*(T b)
		{
			vector3<T> res;
			res.x = x * b;
			res.y = y * b;
			res.z = z * b;
			return res;
		}

		vector3<T>& operator+(vector3<T>& b)
		{
			x += b.x;
			y += b.y;
			z += b.z;
			return *this;
		}

		vector3<T>& operator*=(T&& b)
		{
			x *= b;
			y *= b;
			z *= b;
			return *this;
		}

	};

	typedef vector3<float> VEC3;
}

