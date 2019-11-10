#include "JsonTextReader.hpp"

Elysium::Core::Json::JsonTextReader::JsonTextReader(Elysium::Core::IO::TextReader & Reader)
	: _Reader(Reader)
{
}
Elysium::Core::Json::JsonTextReader::~JsonTextReader()
{
}
