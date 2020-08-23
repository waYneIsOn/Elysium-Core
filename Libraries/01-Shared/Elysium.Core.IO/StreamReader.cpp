#include "StreamReader.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::IO::StreamReader::StreamReader(Stream & InputStream, const Text::Encoding& Encoding, const bool DetecEncodingFromByteOrderMarks, const Elysium::Core::int32_t MinimumBufferSize, const bool LeaveOpen)
	: Elysium::Core::IO::TextReader(),
	_Position(0), _InputStream(InputStream), _Encoding(Encoding),
	_LeaveOpen(LeaveOpen)
{ }
Elysium::Core::IO::StreamReader::~StreamReader()
{
	if (!_LeaveOpen)
	{
		Close();
	}
}

void Elysium::Core::IO::StreamReader::Close()
{
	_InputStream.Close();
}

const Elysium::Core::int32_t Elysium::Core::IO::StreamReader::Peek()
{
	throw NotImplementedException();
}

const Elysium::Core::int32_t Elysium::Core::IO::StreamReader::Read()
{
	throw NotImplementedException();
}

Elysium::Core::String Elysium::Core::IO::StreamReader::ReadLine()
{
	throw NotImplementedException();
}

Elysium::Core::String Elysium::Core::IO::StreamReader::ReadToEnd()
{
	throw NotImplementedException();
}
