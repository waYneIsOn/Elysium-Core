#include "JsonTextReader.hpp"

Elysium::Core::Json::JsonTextReader::JsonTextReader(Elysium::Core::IO::TextReader & Reader)
	: JsonReader(JsonIOSettings()),
	_Reader(Reader)
{
}
Elysium::Core::Json::JsonTextReader::JsonTextReader(const JsonIOSettings & IOSettings, Elysium::Core::IO::TextReader & Reader)
	: JsonReader(IOSettings),
	_Reader(Reader)
{
}
Elysium::Core::Json::JsonTextReader::~JsonTextReader()
{
}

const int32_t Elysium::Core::Json::JsonTextReader::PeekNextCharacterFromSource()
{
	return _Reader.Peek();
}
const int32_t Elysium::Core::Json::JsonTextReader::ReadNextCharacterFromSource()
{
	return _Reader.Read();
}
