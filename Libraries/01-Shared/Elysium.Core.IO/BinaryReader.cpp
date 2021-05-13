#include "BinaryReader.hpp"

Elysium::Core::IO::Compression::BinaryReader::BinaryReader(Stream& BaseStream, const Elysium::Core::Text::Encoding& Encoding, const bool LeaveOpen)
	: _BaseStream(BaseStream), _Encoding(Encoding), _LeaveOpen(LeaveOpen),
	// ToDo: length?
	_Buffer(16)
{ }

Elysium::Core::IO::Compression::BinaryReader::~BinaryReader()
{
	if (!_LeaveOpen)
	{
		_BaseStream.Close();
	}
}

Elysium::Core::IO::Stream& Elysium::Core::IO::Compression::BinaryReader::GetBaseStream() const
{
	return _BaseStream;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::IO::Compression::BinaryReader::ReadBytes(const Elysium::Core::uint32_t Count)
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Data = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(Count);

	Elysium::Core::uint32_t BytesRead = 0;
	do
	{
		BytesRead += static_cast<Elysium::Core::uint32_t>(_BaseStream.Read(&Data[BytesRead], Count));
	} while (BytesRead < Count);

	return Data;
}

const Elysium::Core::uint16_t Elysium::Core::IO::Compression::BinaryReader::ReadUInt16()
{
	_BaseStream.Read(&_Buffer[0], sizeof(Elysium::Core::uint16_t));
	return uint16_t(_Buffer[0] | _Buffer[1] << 8);
}

const Elysium::Core::uint32_t Elysium::Core::IO::Compression::BinaryReader::ReadUInt32()
{
	_BaseStream.Read(&_Buffer[0], sizeof(Elysium::Core::uint32_t));
	return uint32_t(_Buffer[0] | _Buffer[1] << 8 | _Buffer[2] << 16 | _Buffer[3] << 24);
}
