#ifndef __NET_SERVER__PACKET_H___
#define __NET_SERVER__PACKET_H___
#include <vector>
#include <memory>
#include <algorithm>
#include <string.h>

namespace google
{
	namespace protobuf
	{
		class Message;
	}
}

namespace game_net
{

	//std::string string_To_UTF8(const std::string & str)
	//{
	//	int nwLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	//	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	//	ZeroMemory(pwBuf, nwLen * 2 + 2);

	//	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	//	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	//	char * pBuf = new char[nLen + 1];
	//	ZeroMemory(pBuf, nLen + 1);

	//	WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	//	std::string retStr(pBuf);

	//	delete[]pwBuf;
	//	delete[]pBuf;

	//	pwBuf = NULL;
	//	pBuf = NULL;

	//	return retStr;
	//};

	//std::string UTF8_To_string(const std::string & str)
	//{
	//	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	//	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	//	memset(pwBuf, 0, nwLen * 2 + 2);

	//	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	//	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	//	char * pBuf = new char[nLen + 1];
	//	memset(pBuf, 0, nLen + 1);

	//	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	//	std::string retStr = pBuf;

	//	delete[]pBuf;
	//	delete[]pwBuf;

	//	pBuf = NULL;
	//	pwBuf = NULL;

	//	return retStr;
	//}


	struct PacketHeader
	{
		uint32_t opCode;
		uint32_t length;
	};

	struct ServerPacket
	{
	public:
		ServerPacket(uint32_t opCode, uint8_t* data, uint32_t length)
		{
			header.opCode = opCode;
			header.length = length;
			body.resize(length);
			memcpy(body.data(), data, length);
		}

		ServerPacket(uint32_t opCode, uint32_t length)
		{
			header.opCode = opCode;
			header.length = length;
			body.resize(length);
		}

		ServerPacket(uint32_t opCode = 0)
		{
			header.opCode = opCode;
			header.length = 0;
		}

		int PacketSize() const
		{
			return sizeof(PacketHeader) + body.size();
		}

		void Write(int value)
		{
			WriteBytes((uint8_t*)&value, sizeof(value));
		}

		void Read(int& value)
		{
			ReadBytes((uint8_t*)&value, sizeof(value));
		}

		void Write(float value)
		{
			WriteBytes((uint8_t*)&value, sizeof(value));
		}

		void Read(float& value)
		{
			ReadBytes((uint8_t*)&value, sizeof(value));
		}

		void Write(double value)
		{
			WriteBytes((uint8_t*)&value, sizeof(value));
		}

		void Read(double& value)
		{
			ReadBytes((uint8_t*)&value, sizeof(value));
		}

		void Write(bool value)
		{
			WriteBytes((uint8_t*)&value, sizeof(value));
		}

		void Read(bool& value)
		{
			ReadBytes((uint8_t*)&value, sizeof(value));
		}

		void Write(std::string& value)
		{
			//std::string to_value = string_To_UTF8(value);
			int length = value.length();
			WriteBytes((uint8_t*)&length, sizeof(length));
			WriteBytes((uint8_t*)value.data(), length);
		}

		void Read(std::string& rs)
		{
			int length = 0;
			ReadBytes((uint8_t*)&length, sizeof(length));
			//std::string rs;
			rs.reserve(length);
			ReadBytes((uint8_t*)rs.data(), length);
			//value = UTF8_To_string(rs);
		}

		void Write(std::wstring& value)
		{
			//std::string to_value = string_To_UTF8(value);
			int length = value.length();
			WriteBytes((uint8_t*)&length, sizeof(length));
			WriteBytes((uint8_t*)value.data(), length);
		}

		void Read(std::wstring& rs)
		{
			int length = 0;
			ReadBytes((uint8_t*)&length, sizeof(length));
			//std::string rs;
			rs.reserve(length);
			ReadBytes((uint8_t*)rs.data(), length);
			//value = UTF8_To_string(rs);
		}

		void WriteBytes(uint8_t* data, uint32_t length)
		{
			if (body.size() < length + _write_idx)
			{
				body.reserve(std::max(body.size() * 2, (unsigned int)length + _write_idx));
			}
			body.resize(_write_idx + length);
			memcpy(body.data() + _write_idx, data, length);
			_write_idx += length;
		}

		void ReadBytes(uint8_t* data, uint32_t length)
		{
			memcpy(data, body.data() + _read_idx, length);
			_read_idx += length;
		}

		void WriteTo(uint8_t* data, uint32_t length)
		{
			if (length < PacketSize())
			{
				return;
			}
			header.length = _write_idx;

			memcpy(data, &header, sizeof(PacketHeader));
			memcpy(data + sizeof(PacketHeader), body.data(), _write_idx);
		}

		bool WriteTo(google::protobuf::Message& msg);
		bool ReadFrom(const google::protobuf::Message& msg);

		~ServerPacket()
		{

		}
		PacketHeader header;
		std::vector<uint8_t> body;
		uint32_t _write_idx = 0;
		uint32_t _read_idx = 0;
	};

	typedef std::shared_ptr<ServerPacket> PacketPtr;
	struct packet_header
	{
		uint32_t length : 14;
		uint32_t opCode;
	};

	struct packet
	{
		packet(uint32_t opcode);
		packet(uint32_t opcode, uint8_t* data, uint32_t length);
		packet(uint8_t* data, uint32_t length);

		uint32_t Opcode() const
		{
			_header.opCode;
		}

		uint32_t Length() const
		{
			return _content.size();
		}

		const uint8_t* Data() const
		{
			return _content.data() + sizeof(packet_header);
		}

		uint32_t ContentLength() const
		{
			return _content.size() - sizeof(packet_header);
		}

		const uint8_t* Content() const
		{
			return _content.data() + sizeof(packet_header);
		}

	private:
		packet_header _header;
		std::vector<uint8_t> _content;
	};

}
#endif