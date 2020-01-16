#include "StreamReader.hpp"

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::IO::StreamReader::StreamReader(Stream & InputStream)
	: Elysium::Core::IO::TextReader(),
	_Position(0), _InputStream(InputStream)
{
}
Elysium::Core::IO::StreamReader::~StreamReader()
{
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

Elysium::Core::StringView Elysium::Core::IO::StreamReader::ReadLine()
{
	throw NotImplementedException();
}

Elysium::Core::StringView Elysium::Core::IO::StreamReader::ReadToEnd()
{
	throw NotImplementedException();
}
