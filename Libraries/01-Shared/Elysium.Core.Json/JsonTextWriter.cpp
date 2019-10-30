#include "JsonTextWriter.hpp"

#ifndef _REGEX_
#include <regex>
#endif

Elysium::Core::Json::JsonTextWriter::JsonTextWriter(Elysium::Core::IO::TextWriter & Writer)
	: Elysium::Core::Json::JsonWriter(),
	_Writer(Writer)
{
}
Elysium::Core::Json::JsonTextWriter::~JsonTextWriter()
{
}

void Elysium::Core::Json::JsonTextWriter::WriteStartObject()
{
#ifdef UNICODE
	_Writer.Write(L'{');
#else
	_Writer.Write('{');
#endif
}
void Elysium::Core::Json::JsonTextWriter::WriteEndObject()
{
#ifdef UNICODE
	_Writer.Write(L'}');
#else
	_Writer.Write('}');
#endif
}

void Elysium::Core::Json::JsonTextWriter::WriteStartArray()
{
#ifdef UNICODE
	_Writer.Write(L'[');
#else
	_Writer.Write('[');
#endif
}
void Elysium::Core::Json::JsonTextWriter::WriteEndArray()
{
#ifdef UNICODE
	_Writer.Write(L']');
#else
	_Writer.Write(']');
#endif
}

void Elysium::Core::Json::JsonTextWriter::WritePropertyName(const String & Name)
{
	// [A-Za-z\s]	// A-Z and a-z and whitespaces
	// [A-Za-z]	// A-Z and a-z
	//std::regex_match()

	// ToDo: quoting, escaping, (no numbers - can a name contain anything really???) etc.
	_Writer.Write(Name);

#ifdef UNICODE
	_Writer.Write(L':');
#else
	_Writer.Write(':');
#endif
}

void Elysium::Core::Json::JsonTextWriter::WriteValue(const int & Value)
{
	// ToDo: exponent!! (does std::to_string(...) already handle that for us?)
	_Writer.Write(Value);
}
void Elysium::Core::Json::JsonTextWriter::WriteValue(const String & Value)
{
	// ToDo: quoting, escaping, maybe encoding (utf-8 and 16 possible)
	_Writer.Write(Value);
}

void Elysium::Core::Json::JsonTextWriter::WriteNull()
{
#ifdef UNICODE
	_Writer.Write(L"null");
#else
	_Writer.Write("null");
#endif
}

void Elysium::Core::Json::JsonTextWriter::WriteComment(const String & Comment)
{
#ifdef UNICODE
	_Writer.Write(L"/*");
#else
	_Writer.Write("/*");
#endif
	_Writer.Write(Comment);
#ifdef UNICODE
	_Writer.Write(L"*/");
#else
	_Writer.Write("*/");
#endif
}

void Elysium::Core::Json::JsonTextWriter::WriteIndent()
{






	const Elysium::Core::String& NewLine = _Writer.GetNewLine();
	// ToDo








}
void Elysium::Core::Json::JsonTextWriter::WriteValueDelimiter()
{
#ifdef UNICODE
	_Writer.Write(L',');
#else
	_Writer.Write(',');
#endif
}
void Elysium::Core::Json::JsonTextWriter::WriteIndentSpace()
{
#ifdef UNICODE
	_Writer.Write(L' ');
#else
	_Writer.Write(' ');
#endif
}
