#include "JsonTextWriter.hpp"

Elysium::Core::Json::JsonTextWriter::JsonTextWriter(Elysium::Core::IO::TextWriter & Writer)
	: Elysium::Core::Json::JsonWriter(),
	_Writer(Writer)
{
}
Elysium::Core::Json::JsonTextWriter::~JsonTextWriter()
{
}

void Elysium::Core::Json::JsonTextWriter::WriteString(const char & Value)
{
	_Writer.Write(Value);
}
void Elysium::Core::Json::JsonTextWriter::WriteString(const wchar_t & Value)
{
	_Writer.Write(Value);
}
void Elysium::Core::Json::JsonTextWriter::WriteString(const String & Value)
{
	_Writer.Write(Value);
}
