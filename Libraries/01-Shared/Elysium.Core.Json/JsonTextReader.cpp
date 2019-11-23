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

const ElysiumChar Elysium::Core::Json::JsonTextReader::GetChar(uint32_t Index)
{
	return _Reader.Read();
}
