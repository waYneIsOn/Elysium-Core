#include "TextWriter.hpp"


#ifndef ELYSIUM_CORE_BOOLEAN
#include "../Elysium.Core/Boolean.hpp"
#endif

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Convert.hpp"
#endif

Elysium::Core::IO::TextWriter::TextWriter()
	: _NewLineCharacters(Environment::NewLine)
{ }

Elysium::Core::IO::TextWriter::~TextWriter()
{
	Flush();
	Close();
}

const Elysium::Core::Text::Encoding & Elysium::Core::IO::TextWriter::GetEncoding()
{
	return Elysium::Core::Text::Encoding::Default();
}

const Elysium::Core::Utf8String & Elysium::Core::IO::TextWriter::GetNewLine()
{
	return _NewLineCharacters;
}

void Elysium::Core::IO::TextWriter::SetNewLine(const Elysium::Core::Utf8String& NewLine)
{
	_NewLineCharacters = NewLine;
}

void Elysium::Core::IO::TextWriter::Close()
{ }

void Elysium::Core::IO::TextWriter::Flush()
{ }

void Elysium::Core::IO::TextWriter::Write(const bool Value)
{
	Write(Value == true ? Elysium::Core::Boolean::TrueString : Elysium::Core::Boolean::FalseString);
}

void Elysium::Core::IO::TextWriter::Write(const byte Value)
{
	Write(&Value, 1);
}

void Elysium::Core::IO::TextWriter::Write(const char8_t Value)
{
	Write(static_cast<const byte>(Value));
}

void Elysium::Core::IO::TextWriter::Write(const char8_t * Value, const Elysium::Core::size Count)
{
	Elysium::Core::Container::VectorOfByte Bytes = GetEncoding().GetBytes(Value, Count);
	Write(&Bytes[0], Bytes.GetLength());
}

void Elysium::Core::IO::TextWriter::Write(const float Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10));
}

void Elysium::Core::IO::TextWriter::Write(const double Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10));
}

void Elysium::Core::IO::TextWriter::Write(const Decimal & Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value.GetHighPart(), 10));
	Write(u8".");
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value.GetLowPart(), 10));
}

void Elysium::Core::IO::TextWriter::Write(const int16_t Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10));
}

void Elysium::Core::IO::TextWriter::Write(const int32_t Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10));
}

void Elysium::Core::IO::TextWriter::Write(const int64_t Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10));
}

void Elysium::Core::IO::TextWriter::Write(const uint16_t Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10));
}

void Elysium::Core::IO::TextWriter::Write(const uint32_t Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10));
}

void Elysium::Core::IO::TextWriter::Write(const uint64_t Value)
{
	Write(Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10));
}

void Elysium::Core::IO::TextWriter::Write(const Elysium::Core::Utf8String& Value)
{
	Write(&Value[0], Value.GetLength());
}

void Elysium::Core::IO::TextWriter::WriteLine(const bool Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const byte Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const byte * Value, const Elysium::Core::size Count)
{
	Write(Value, Count);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const char8_t Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const char8_t* Value, const Elysium::Core::size Count)
{
	Write(&Value[0], Count);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const float Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const double Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const Decimal & Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const int16_t Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const int32_t Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const int64_t Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const uint16_t Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const uint32_t Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const uint64_t Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine(const Elysium::Core::Utf8String& Value)
{
	Write(Value);
	WriteLine();
}

void Elysium::Core::IO::TextWriter::WriteLine()
{
	Write(_NewLineCharacters);
}
