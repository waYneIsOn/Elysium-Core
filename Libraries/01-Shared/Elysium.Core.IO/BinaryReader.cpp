#include "BinaryReader.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "../Elysium.Core/ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "../Elysium.Core/ArgumentOutOfRangeException.hpp"
#endif

Elysium::Core::IO::BinaryReader::BinaryReader(Stream& InputStream, Elysium::Core::Text::Encoding& Encoding, const bool LeaveOpen)
	: _InputStream(InputStream), _Encoding(Encoding), _LeaveOpen(LeaveOpen),
	_Buffer(DefaultBufferSize)
{ }

Elysium::Core::IO::BinaryReader::~BinaryReader()
{
	if (!_LeaveOpen)
	{
		Close();
	}
}

Elysium::Core::IO::Stream& Elysium::Core::IO::BinaryReader::GetBaseStream() const
{
	return _InputStream;
}

void Elysium::Core::IO::BinaryReader::Close()
{
	_InputStream.Close();
}

const bool Elysium::Core::IO::BinaryReader::ReadBoolean()
{
	FillBuffer(1);
	return _Buffer[0] == 0;
}

const Elysium::Core::byte Elysium::Core::IO::BinaryReader::ReadByte()
{
	FillBuffer(1);
	return _Buffer[0];
}

const size_t Elysium::Core::IO::BinaryReader::ReadBytes(Elysium::Core::byte* Buffer, const size_t Count)
{
	if (Buffer == nullptr)
	{
		throw ArgumentNullException(u8"Buffer");
	}

	if (Count == 0)
	{
		return 0;
	}

	size_t TotalBytesRead = 0;
	do
	{
		const size_t BytesRead = _InputStream.Read(&Buffer[TotalBytesRead], Count - TotalBytesRead);
		if (BytesRead == 0)
		{
			break;
		}
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < Count);

	return TotalBytesRead;
}

const double Elysium::Core::IO::BinaryReader::ReadDouble()
{
	FillBuffer(8);
	Elysium::Core::uint32_t Low = Elysium::Core::uint32_t(_Buffer[0] | _Buffer[1] << 8 | _Buffer[2] << 16 | _Buffer[3] << 24);
	Elysium::Core::uint32_t High = Elysium::Core::uint32_t(_Buffer[4] | _Buffer[5] << 8 | _Buffer[6] << 16 | _Buffer[7] << 24);
	Elysium::Core::uint64_t Temporary = static_cast<Elysium::Core::uint64_t>(High) << 32 | Low;

	return static_cast<double>(Temporary);
}

const Elysium::Core::int16_t Elysium::Core::IO::BinaryReader::ReadInt16()
{
	FillBuffer(2);
	return Elysium::Core::uint16_t(_Buffer[0] | _Buffer[1] << 8);
}

const Elysium::Core::int32_t Elysium::Core::IO::BinaryReader::ReadInt32()
{
	FillBuffer(4);
	return Elysium::Core::uint32_t(_Buffer[0] | _Buffer[1] << 8 | _Buffer[2] << 16 | _Buffer[3] << 24);
}

const Elysium::Core::int64_t Elysium::Core::IO::BinaryReader::ReadInt64()
{
	FillBuffer(8);
	Elysium::Core::uint32_t Low = Elysium::Core::uint32_t(_Buffer[0] | _Buffer[1] << 8 | _Buffer[2] << 16 | _Buffer[3] << 24);
	Elysium::Core::uint32_t High = Elysium::Core::uint32_t(_Buffer[4] | _Buffer[5] << 8 | _Buffer[6] << 16 | _Buffer[7] << 24);

	return static_cast<Elysium::Core::uint64_t>(High) << 32 | Low;
}

const float Elysium::Core::IO::BinaryReader::ReadSingle()
{
	FillBuffer(4);
	Elysium::Core::uint32_t Temporary = Elysium::Core::uint32_t(_Buffer[0] | _Buffer[1] << 8 | _Buffer[2] << 16 | _Buffer[3] << 24);

	return static_cast<float>(Temporary);
}

const Elysium::Core::uint16_t Elysium::Core::IO::BinaryReader::ReadUInt16()
{
	FillBuffer(2);
	return Elysium::Core::uint16_t(_Buffer[0] | _Buffer[1] << 8);
}

const Elysium::Core::uint32_t Elysium::Core::IO::BinaryReader::ReadUInt32()
{
	FillBuffer(4);
	return Elysium::Core::uint32_t(_Buffer[0] | _Buffer[1] << 8 | _Buffer[2] << 16 | _Buffer[3] << 24);
}

const Elysium::Core::uint64_t Elysium::Core::IO::BinaryReader::ReadUInt64()
{
	FillBuffer(8);
	Elysium::Core::uint32_t Low = Elysium::Core::uint32_t(_Buffer[0] | _Buffer[1] << 8 | _Buffer[2] << 16 | _Buffer[3] << 24);
	Elysium::Core::uint32_t High = Elysium::Core::uint32_t(_Buffer[4] | _Buffer[5] << 8 | _Buffer[6] << 16 | _Buffer[7] << 24);

	return static_cast<Elysium::Core::uint64_t>(High) << 32 | Low;
}

void Elysium::Core::IO::BinaryReader::FillBuffer(const size_t Count)
{
	if (Count > _Buffer.GetLength())
	{
		throw ArgumentOutOfRangeException(u8"Count");
	}

	if (Count == 1)
	{	// circumvent the more complex code down below
		Elysium::Core::byte Byte = _InputStream.ReadByte();
		_Buffer[0] = Byte;
		return;
	}

	size_t TotalBytesRead = 0;
	do
	{
		const size_t BytesRead = _InputStream.Read(&_Buffer[TotalBytesRead], Count - TotalBytesRead);
		if (BytesRead == 0)
		{
			break;
		}
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < Count);
}

