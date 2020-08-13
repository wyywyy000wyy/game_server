#pragma once
#include <vector>
#include <type_traits>
#include <boost/type_traits.hpp>
#include <boost/tti/has_member_function.hpp>

#include "Packet.h"
namespace game_net
{
	struct HasMemberToStringValidator
	{
		template <typename T, typename = decltype(&T::serialize)>
		static std::true_type Test(int);

		template <typename>
		static std::false_type Test(...);
	};

	template <typename T>
	struct HasMemberToString :
		public decltype(HasMemberToStringValidator::Test<T>(0))
	{};

	struct PacketWriterDefault {
		
		template<typename T>
		static void Write(PacketPtr packet,T& value) { packet->Write(value); };
	};

	struct PacketWriterSerialize {
		template<typename T>
		static void Write(PacketPtr packet, T&& value) { value.serialize(packet); };
	};

	struct PacketReaderDefault {

		template<typename T>
		static void Read(PacketPtr packet, T& value) { packet->Read(value); };
	};

	struct PacketReaderSerialize {
		template<typename T>
		static void Read(PacketPtr packet, T&& value) { value.unserialize(packet); };
	};

	template<typename T>
	struct PacketWriter {
		typedef std::conditional<HasMemberToString<T>::value, PacketWriterSerialize, PacketWriterDefault> Type;
	};

	template<typename T>
	struct PacketReader{
		typedef std::conditional<HasMemberToString<T>::value, PacketReaderSerialize, PacketReaderDefault> Type;
	};

}

#define PACK_MSG_0(MSG_NAME, OP_CODE) \
	struct MSG_NAME { \
		MSG_NAME(){ \
		} \
		game_net::PacketPtr packet; \
		game_net::PacketPtr Serialize() {\
			packet = std::make_shared<game_net::ServerPacket>(OP_CODE, 0); \
		}\
		void Unserialize(game_net::PacketPtr packet) {\
		}\
	};


#define PACK_MSG_ONE_(TYPE, NAME) \
	game_net::PacketWriter<TYPE>::Type::type::Write(packet,NAME);

#define READ_MSG_ONE_(TYPE, NAME) \
	game_net::PacketReader<TYPE>::Type::type::Read(packet,NAME);

#define PACK_MSG_1(MSG_NAME, OP_CODE ,TYPE0, NAME0) \
	struct MSG_NAME { \
		MSG_NAME(){ \
		} \
		TYPE0 NAME0; \
		game_net::PacketPtr Serialize() {\
			game_net::PacketPtr packet = std::make_shared<game_net::ServerPacket>(OP_CODE); \
			PACK_MSG_ONE_(TYPE0, NAME0);\
			return packet;\
		}\
		void Unserialize(game_net::PacketPtr packet) {\
			READ_MSG_ONE_(TYPE0, NAME0);\
		}\
	};

#define PACK_MSG_2(MSG_NAME, OP_CODE ,TYPE0, NAME0, TYPE1, NAME1) \
	struct MSG_NAME { \
		MSG_NAME(){ \
		} \
		TYPE0 NAME0; \
		TYPE1 NAME1; \
		game_net::PacketPtr Serialize() {\
			game_net::PacketPtr packet = std::make_shared<game_net::ServerPacket>(OP_CODE); \
			PACK_MSG_ONE_(TYPE0, NAME0);\
			PACK_MSG_ONE_(TYPE1, NAME1);\
			return packet;\
		}\
		void Unserialize(game_net::PacketPtr packet) {\
			READ_MSG_ONE_(TYPE0, NAME0);\
			READ_MSG_ONE_(TYPE1, NAME1);\
		}\
	};

#define PACK_MSG_3(MSG_NAME, OP_CODE ,TYPE0, NAME0, TYPE1, NAME1, TYPE2, NAME2) \
	struct MSG_NAME { \
		MSG_NAME(){ \
		} \
		TYPE0 NAME0; \
		TYPE1 NAME1; \
		TYPE2 NAME2; \
		game_net::PacketPtr Serialize() {\
			game_net::PacketPtr packet = std::make_shared<game_net::ServerPacket>(OP_CODE); \
			PACK_MSG_ONE_(TYPE0, NAME0);\
			PACK_MSG_ONE_(TYPE1, NAME1);\
			PACK_MSG_ONE_(TYPE2, NAME2);\
			return packet;\
		}\
		void Unserialize(game_net::PacketPtr packet) {\
			READ_MSG_ONE_(TYPE0, NAME0);\
			READ_MSG_ONE_(TYPE1, NAME1);\
			READ_MSG_ONE_(TYPE2, NAME2);\
		}\
	};

#define PACK_MSG_4(MSG_NAME, OP_CODE ,TYPE0, NAME0, TYPE1, NAME1, TYPE2, NAME2, TYPE3, NAME3) \
	struct MSG_NAME { \
		MSG_NAME(){ \
		} \
		TYPE0 NAME0; \
		TYPE1 NAME1; \
		TYPE2 NAME2; \
		TYPE3 NAME3; \
		game_net::PacketPtr Serialize() {\
			game_net::PacketPtr packet = std::make_shared<game_net::ServerPacket>(OP_CODE); \
			PACK_MSG_ONE_(TYPE0, NAME0);\
			PACK_MSG_ONE_(TYPE1, NAME1);\
			PACK_MSG_ONE_(TYPE2, NAME2);\
			PACK_MSG_ONE_(TYPE3, NAME3);\
			return packet;\
		}\
		void Unserialize(game_net::PacketPtr packet) {\
			READ_MSG_ONE_(TYPE0, NAME0);\
			READ_MSG_ONE_(TYPE1, NAME1);\
			READ_MSG_ONE_(TYPE2, NAME2);\
			READ_MSG_ONE_(TYPE3, NAME3);\
		}\
	};