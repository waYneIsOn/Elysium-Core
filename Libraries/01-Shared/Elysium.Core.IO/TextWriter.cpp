#include "TextWriter.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef ELYSIUM_CORE_BOOLEAN
#include "../Elysium.Core/Boolean.hpp"
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::IO::TextWriter::~TextWriter()
{
	Flush();
	Close();
}

const Elysium::Core::Text::Encoding & Elysium::Core::IO::TextWriter::GetEncoding()
{
	return Elysium::Core::Text::Encoding::Default();
}

const Elysium::Core::String & Elysium::Core::IO::TextWriter::GetNewLine()
{
	return _NewLineCharacters;
}

void Elysium::Core::IO::TextWriter::SetNewLine(const String & NewLine)
{
	_NewLineCharacters = NewLine;
}

void Elysium::Core::IO::TextWriter::Close()
{
}
void Elysium::Core::IO::TextWriter::Flush()
{
}

void Elysium::Core::IO::TextWriter::Write(const bool & Value)
{
	Write(Value == true ? Elysium::Core::Boolean::TrueLiteral : Elysium::Core::Boolean::FalseLiteral);
}
void Elysium::Core::IO::TextWriter::Write(const byte & Value)
{
	Write(&Value, 0, 1);
}
void Elysium::Core::IO::TextWriter::Write(const byte * Value, const size_t Count)
{
	Write(Value, 0, Count);
}
void Elysium::Core::IO::TextWriter::Write(const byte * Value, const size_t Index, const size_t Count)
{
}
void Elysium::Core::IO::TextWriter::Write(const char16_t Value)
{
	Elysium::Core::Collections::Generic::List<byte> Bytes = GetEncoding().GetBytes(Value);
	Write(&Bytes[0], Bytes.GetCount());
}
void Elysium::Core::IO::TextWriter::Write(const char16_t * Value, const size_t Count)
{
	Elysium::Core::Collections::Generic::List<byte> Bytes = GetEncoding().GetBytes(Value, 0, Count);
	Write(&Bytes[0], Bytes.GetCount());
}
void Elysium::Core::IO::TextWriter::Write(const float & Value)
{
	Write(std::to_wstring(Value).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const double & Value)
{
	Write(std::to_wstring(Value).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const Decimal & Value)
{
	Write(std::to_wstring(*Value.GetHighPart()).c_str());
	Write(u".");
	Write(std::to_wstring(*Value.GetLowPart()).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const int16_t & Value)
{
	Write(std::to_wstring(Value).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const int32_t & Value)
{
	Write(std::to_wstring(Value).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const int64_t & Value)
{
	Write(std::to_wstring(Value).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const uint16_t & Value)
{
	Write(std::to_wstring(Value).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const uint32_t & Value)
{
	Write(std::to_wstring(Value).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const uint64_t & Value)
{
	Write(std::to_wstring(Value).c_str());
}
void Elysium::Core::IO::TextWriter::Write(const String & Value)
{
	Write(&Value.GetCharArray()[0], Value.GetLength());
}

void Elysium::Core::IO::TextWriter::WriteLine(const bool & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const byte & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const byte * Value, const size_t Count)
{
	Write(Value, 0, Count);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const char16_t & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const char16_t * Value, const size_t Count)
{
	Write(&Value[0], Count);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const float & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const double & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const Decimal & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const int16_t & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const int32_t & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const int64_t & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const uint16_t & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const uint32_t & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const uint64_t & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine(const String & Value)
{
	Write(Value);
	WriteLine();
}
void Elysium::Core::IO::TextWriter::WriteLine()
{
	Write(_NewLineCharacters);
}

Elysium::Core::IO::TextWriter::TextWriter()
	: _NewLineCharacters(Elysium::Core::String(Environment::NewLine()))
{
}
