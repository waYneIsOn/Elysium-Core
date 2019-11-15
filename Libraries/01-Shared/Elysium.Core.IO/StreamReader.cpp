#include "StreamReader.hpp"

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
