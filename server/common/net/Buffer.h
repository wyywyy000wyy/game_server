#pragma once
#include <vector>
#include "Packet.h"

namespace game_net
{

	class ServerBuffer
	{
	public:
		ServerBuffer(int size = 4096);

		uint8_t* WritePtr()
		{
			return m_buffer[m_curIndex].data() + m_pos;
		}

		uint8_t* Data()
		{
			return m_buffer[m_curIndex].data();
		}

		int DataLength() const
		{
			return m_pos;
		}

		int Size() const { return m_buffer[m_curIndex].size(); }

		void WriteFrom(PacketPtr p);

		void Resize(int length);

		void Write(const uint8_t* buffer, int length, int offset = -1);

		int Read(uint8_t* buffer, int bufferLength, int offset = -1);

		int pos() const { return m_pos; }

		void swapInOut();
	private:
		int m_pos;
		int m_rpos;
		int m_curIndex;
		std::vector<uint8_t> m_buffer[2];
	};
}
