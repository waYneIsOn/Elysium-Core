#include "StreamReader.hpp"

Elysium::Core::IO::StreamReader::StreamReader(Stream & InputStream)
	: Elysium::Core::IO::TextReader(),
	_InputStream(InputStream)
{
}
Elysium::Core::IO::StreamReader::~StreamReader()
{
}

void Elysium::Core::IO::StreamReader::Close()
{
	_InputStream.Close();
}

int Elysium::Core::IO::StreamReader::Peek()
{
	return -1;
	//return _InputStream.Peek();
}
