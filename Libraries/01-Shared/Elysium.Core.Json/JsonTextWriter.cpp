#include "JsonTextWriter.hpp"

Elysium::Core::Json::JsonTextWriter::JsonTextWriter(Elysium::Core::IO::TextWriter & Writer)
	: Elysium::Core::Json::JsonWriter(JsonIOSettings()),
	_Writer(Writer)
{
}
Elysium::Core::Json::JsonTextWriter::JsonTextWriter(const JsonIOSettings& IOSettings, Elysium::Core::IO::TextWriter& Writer)
	: Elysium::Core::Json::JsonWriter(IOSettings),
	_Writer(Writer)
{
}
Elysium::Core::Json::JsonTextWriter::~JsonTextWriter()
{
}

void Elysium::Core::Json::JsonTextWriter::WriteString(const char8_t Value)
{
	_Writer.Write(Value);
}
void Elysium::Core::Json::JsonTextWriter::WriteString(const String & Value)
{
	_Writer.Write(Value);
}
