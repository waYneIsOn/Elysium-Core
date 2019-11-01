#include "JsonWriter.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef _REGEX_
#include <regex>
#endif

void Elysium::Core::Json::JsonWriter::WriteStartObject()
{
	_State = JsonWriter::JsonWriterState::StartedObject;

	if (_Depth > 0)
	{
		WriteString(Environment::NewLine());
		for (uint16_t i = 0; i < _Depth; i++)
		{
			WriteIndent();
		}
	}
#ifdef UNICODE
	WriteString(L'{');
#else
	WriteString('{');
#endif
	WriteString(Environment::NewLine());
	_Depth++;
}
void Elysium::Core::Json::JsonWriter::WriteEndObject()
{
	WriteString(Environment::NewLine());
	for (uint16_t i = 0; i < _Depth - 1; i++)
	{
		WriteIndent();
	}
#ifdef UNICODE
	WriteString(L'}');
#else
	WriteString('}');
#endif
	_Depth--;

	if (_Depth == 0)
	{
		_State = JsonWriter::JsonWriterState::Finished;
	}
}

void Elysium::Core::Json::JsonWriter::WriteStartArray()
{
	_State = JsonWriter::JsonWriterState::StartedArray;

	WriteString(Environment::NewLine());
	for (uint16_t i = 0; i < _Depth; i++)
	{
		WriteIndent();
	}
#ifdef UNICODE
	WriteString(L'[');
#else
	WriteString('[');
#endif
	_Depth++;
}
void Elysium::Core::Json::JsonWriter::WriteEndArray()
{
	WriteString(Environment::NewLine());
	for (uint16_t i = 0; i < _Depth - 1; i++)
	{
		WriteIndent();
	}
#ifdef UNICODE
	WriteString(L']');
#else
	WriteString(']');
#endif
	_Depth--;
}

void Elysium::Core::Json::JsonWriter::WritePropertyName(const String & Name)
{
	if (_State == JsonWriter::JsonWriterState::StartedProperty || _State == JsonWriter::JsonWriterState::StartedArray)
	{
#ifdef UNICODE
		WriteString(L',');
#else
		WriteString(',');
#endif
		WriteString(Environment::NewLine());
	}
	_State = JsonWriter::JsonWriterState::StartedProperty;

	for (uint16_t i = 0; i < _Depth; i++)
	{
		WriteIndent();
	}

#ifdef UNICODE
	WriteString(L'"');
#else
	WriteString('"');
#endif
	// [A-Za-z\s]	// A-Z and a-z and whitespaces
	// [A-Za-z]	// A-Z and a-z
	//std::regex_match()
	// ToDo: quoting, escaping, (no numbers - can a name contain anything really???) etc.
	WriteString(Name);
#ifdef UNICODE
	WriteString(L'"');
#else
	WriteString('"');
#endif
#ifdef UNICODE
	WriteString(L':');
#else
	WriteString(':');
#endif
}

void Elysium::Core::Json::JsonWriter::WriteValue(const bool & Value)
{
	if (_State == JsonWriter::JsonWriterState::StartedProperty)
	{
		WriteIndentSpace();
	}
#ifdef UNICODE
	WriteString(Value ? L"true" : L"false");
#else
	WriteString(Value ? "true" : "false");
#endif
}
void Elysium::Core::Json::JsonWriter::WriteValue(const int & Value)
{
	if (_State == JsonWriter::JsonWriterState::StartedProperty)
	{
		WriteIndentSpace();
	}
	else if (_State == JsonWriter::JsonWriterState::StartedArray)
	{

#ifdef UNICODE
		WriteString(L',');
#else
		WriteString(',');
#endif

		WriteString(Environment::NewLine());
		for (uint16_t i = 0; i < _Depth; i++)
		{
			WriteIndent();
		}
	}
#ifdef UNICODE
	WriteString(std::to_wstring(Value).c_str());
#else
	WriteString(std::to_string(Value).c_str());
#endif

}
void Elysium::Core::Json::JsonWriter::WriteValue(const float & Value)
{
	if (_State == JsonWriter::JsonWriterState::StartedProperty)
	{
		WriteIndentSpace();
}
#ifdef UNICODE
	WriteString(std::to_wstring(Value).c_str());
#else
	WriteString(std::to_string(Value).c_str());
#endif
}
void Elysium::Core::Json::JsonWriter::WriteValue(const double & Value)
{
	if (_State == JsonWriter::JsonWriterState::StartedProperty)
	{
		WriteIndentSpace();
	}
#ifdef UNICODE
	WriteString(std::to_wstring(Value).c_str());
#else
	WriteString(std::to_string(Value).c_str());
#endif
}
void Elysium::Core::Json::JsonWriter::WriteValue(const wchar_t * Value)
{
	WriteValue(String(Value));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const String & Value)
{
	if (_State == JsonWriter::JsonWriterState::StartedProperty)
	{
		WriteIndentSpace();
	}
#ifdef UNICODE
	WriteString(L'"');
#else
	WriteString('"');
#endif
	// ToDo: quoting, escaping, maybe encoding (utf-8 and 16 possible)
	WriteString(Value);
#ifdef UNICODE
	WriteString(L'"');
#else
	WriteString('"');
#endif
}

void Elysium::Core::Json::JsonWriter::WriteNull()
{
	WriteIndentSpace();
#ifdef UNICODE
	WriteString(L"null");
#else
	WriteString("null");
#endif
}

void Elysium::Core::Json::JsonWriter::WriteComment(const String & Comment)
{
#ifdef UNICODE
	WriteString(L"/*");
#else
	WriteString("/*");
#endif
	WriteString(Comment);
#ifdef UNICODE
	WriteString(L"*/");
#else
	WriteString("*/");
#endif
}

void Elysium::Core::Json::JsonWriter::WriteIndent()
{
#ifdef UNICODE
	WriteString(L"\t");
#else
	WriteString("\t");
#endif
}
void Elysium::Core::Json::JsonWriter::WriteValueDelimiter()
{
#ifdef UNICODE
	WriteString(L',');
#else
	WriteString(',');
#endif
}
void Elysium::Core::Json::JsonWriter::WriteIndentSpace()
{
#ifdef UNICODE
	WriteString(L' ');
#else
	WriteString(' ');
#endif
}

Elysium::Core::Json::JsonWriter::JsonWriter()
	: _State(JsonWriter::JsonWriterState::Initialized), _Depth(0)
{
}
