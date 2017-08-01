#include "Buffer.h"
using namespace game_net;

ServerBuffer::ServerBuffer(int size):m_pos(0), m_curIndex(0), m_rpos(0)
{
	m_buffer[0].resize(size);
	m_buffer[1].resize(size);
}

void ServerBuffer::Resize(int length)
{
	if (length < m_pos + 1 || length < m_rpos + 1)
	{
		return;
	}
	m_buffer[0].resize(length);
	m_buffer[1].resize(length);
}

void ServerBuffer::WriteFrom(PacketPtr p)
{
	int length = p->PacketSize() + m_pos + 1;
	Resize(length);

	p->WriteTo(WritePtr(), p->PacketSize());
	m_pos += p->PacketSize();
}

void ServerBuffer::Write(const uint8_t* buffer, int length, int offset)
{
	if (offset == -1)
	{
		offset = m_pos;
	}
	int needLength = length + offset + 1;
	if (m_buffer[m_curIndex].capacity() < needLength)
	{
		m_buffer[m_curIndex].resize(needLength);
	}

	m_pos = offset + length;
	memcpy(m_buffer[m_curIndex].data() + offset, buffer, length);
}

int ServerBuffer::Read(uint8_t* buffer, int bufferLength, int offset)
{
	if (offset < 0)
	{
		offset = m_rpos;
	}
	if (m_pos <= offset)
	{
		return 0;
	}

	int nRead = m_pos - offset;
	nRead = nRead > bufferLength ? bufferLength: nRead;
	memcpy(buffer, m_buffer[m_curIndex].data() + offset, nRead);

	m_rpos = offset + nRead;
	return nRead;
}

void ServerBuffer::swapInOut()
{
	m_curIndex = (m_curIndex + 1) % 2;
	m_pos = 0;
}