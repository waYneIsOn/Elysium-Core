#include "StringWriter.hpp"

Elysium::Core::IO::StringWriter::StringWriter(Elysium::Core::Text::StringBuilder & StringBuilder)
	: Elysium::Core::IO::TextWriter(),
	_StringBuilder(StringBuilder)
{ }

Elysium::Core::IO::StringWriter::~StringWriter()
{ }

void Elysium::Core::IO::StringWriter::Write(const byte * Value, const Elysium::Core::size Length)
{
	Write(GetEncoding().GetString(&Value[0], Length));
}

void Elysium::Core::IO::StringWriter::Write(const Elysium::Core::Utf8String& Value)
{
	_StringBuilder.Append(&Value[0]);
}
