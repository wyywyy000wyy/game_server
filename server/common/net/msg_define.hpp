#pragma once
#include "PacketTool.hpp"
#include "util/game_math.h"

enum msg_define
{
	C2S_LOGIN = 0x00000001,
	S2C_LOGIN = 0x00000002,

	C2S_MOVE = 0x00010001,
	S2C_MOVE = 0x00010002,

	S2C_PLAYER_BORN = 0x00010003,
	S2C_PLAYER_DESTROY = 0x00010004,
};

//PACK_MSG_1(MSG_C2S_Login, C2S_LOGIN,
//		std::wstring , username
//	);
//
//PACK_MSG_2(MSG_S2C_Login, S2C_LOGIN,
//	std::wstring, username,
//	int, result
//);
//
//PACK_MSG_2(MSG_S2C_ObjectBorn, S2C_PLAYER_BORN,
//	int, player_id_,
//	int, type
//);
//
//PACK_MSG_1(MSG_S2C_ObjectDestroy, S2C_PLAYER_DESTROY,
//	int, player_id_
//);
//
//PACK_MSG_3(MSG_C2S_Move, C2S_MOVE,
//	game_common::VEC3, pos,
//	float, volocity,
//	game_common::VEC3, speed
//);
//
//PACK_MSG_4(MSG_S2C_Move, S2C_MOVE,
//	int, player_id,
//	game_common::VEC3, pos,
//	float, volocity,
//	game_common::VEC3, speed
//);