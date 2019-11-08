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

#ifndef ELYSIUM_CORE_JSON_JSONWRITEREXCEPTION
#include "JsonWriterException.hpp"
#endif

const Elysium::Core::Json::JsonWriter::JsonWriterState Elysium::Core::Json::JsonWriter::_StateLookupTable[9][9] =
{
// AspiredState ->	Initialized					StartedObject						EndedObject						StartedArray					EndedArray,						PropertyName						PropertyValue							Finished					Error
// _State (down)
/*Initialized*/		{ JsonWriterState::Error,	JsonWriterState::StartedObject,		JsonWriterState::Error,			JsonWriterState::StartedArray,	JsonWriterState::Error,			JsonWriterState::Error,				JsonWriterState::Error,			JsonWriterState::Error,		JsonWriterState::Error },
/*StartedObject*/	{ JsonWriterState::Error,	JsonWriterState::Error,				JsonWriterState::EndedObject,	JsonWriterState::Error,			JsonWriterState::Error,			JsonWriterState::PropertyName,		JsonWriterState::Error,			JsonWriterState::Finished,	JsonWriterState::Error },
/*EndedObject*/		{ JsonWriterState::Error,	JsonWriterState::StartedObject,		JsonWriterState::EndedObject,	JsonWriterState::Error,			JsonWriterState::EndedArray,	JsonWriterState::PropertyName,		JsonWriterState::Error,			JsonWriterState::Error,		JsonWriterState::Error },
/*StartedArray*/	{ JsonWriterState::Error,	JsonWriterState::StartedObject,		JsonWriterState::Error,			JsonWriterState::StartedArray,	JsonWriterState::EndedArray,	JsonWriterState::PropertyName,		JsonWriterState::PropertyValue,	JsonWriterState::Error,		JsonWriterState::Error },
/*EndedArray*/		{ JsonWriterState::Error,	JsonWriterState::Error,				JsonWriterState::Error,			JsonWriterState::StartedArray,	JsonWriterState::EndedArray,	JsonWriterState::PropertyName,		JsonWriterState::Error,			JsonWriterState::Finished,	JsonWriterState::Error },
/*PropertyName*/	{ JsonWriterState::Error,	JsonWriterState::StartedObject,		JsonWriterState::Error,			JsonWriterState::StartedArray,	JsonWriterState::Error,			JsonWriterState::Error,				JsonWriterState::PropertyValue,	JsonWriterState::Error,		JsonWriterState::Error },
/*PropertyValue*/	{ JsonWriterState::Error,	JsonWriterState::Error,				JsonWriterState::EndedObject,	JsonWriterState::Error,			JsonWriterState::EndedArray,	JsonWriterState::PropertyName,		JsonWriterState::PropertyValue,	JsonWriterState::Finished,	JsonWriterState::Error },
/*Finished*/		{ JsonWriterState::Error,	JsonWriterState::Error,				JsonWriterState::Error,			JsonWriterState::Error,			JsonWriterState::Error,			JsonWriterState::Error,				JsonWriterState::Error,			JsonWriterState::Error,		JsonWriterState::Error },
/*Error*/			{ JsonWriterState::Error,	JsonWriterState::Error,				JsonWriterState::Error,			JsonWriterState::Error,			JsonWriterState::Error,			JsonWriterState::Error,				JsonWriterState::Error,			JsonWriterState::Error,		JsonWriterState::Error },
};

void Elysium::Core::Json::JsonWriter::WriteStartObject()
{
	JsonWriter::JsonWriterState PreviousState = _State;
	ValidateAndSet(JsonWriter::JsonWriterState::StartedObject);
	if (PreviousState == JsonWriter::JsonWriterState::EndedObject)
	{
#ifdef UNICODE
		WriteString(L',');
#else
		WriteString(',');
#endif
	}

	if (_Depth > 0 && PreviousState != JsonWriter::JsonWriterState::StartedArray)
	{
		WriteIndentSpace();
	}
#ifdef UNICODE
	WriteString(L'{');
#else
	WriteString('{');
#endif
	_Depth++;
}
void Elysium::Core::Json::JsonWriter::WriteEndObject()
{
	JsonWriter::JsonWriterState PreviousState = _State;
	if (_Depth > 1)
	{
		ValidateAndSet(JsonWriter::JsonWriterState::EndedObject);
	}
	else
	{
		ValidateAndSet(JsonWriter::JsonWriterState::Finished);
	}

	if (PreviousState != JsonWriter::JsonWriterState::StartedObject)
	{
		WriteString(Environment::NewLine());
		for (uint16_t i = 0; i < _Depth - 1; i++)
		{
			WriteIndent();
		}
	}
#ifdef UNICODE
	WriteString(L'}');
#else
	WriteString('}');
#endif
	_Depth--;
}

void Elysium::Core::Json::JsonWriter::WriteStartArray()
{
	JsonWriter::JsonWriterState PreviousState = _State;
	ValidateAndSet(JsonWriter::JsonWriterState::StartedArray);
	if (PreviousState == JsonWriter::JsonWriterState::EndedArray)
	{
#ifdef UNICODE
		WriteString(L',');
#else
		WriteString(',');
#endif
	}

	if (PreviousState != JsonWriter::JsonWriterState::StartedArray)
	{
		WriteIndentSpace();
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
	JsonWriter::JsonWriterState PreviousState = _State;
	ValidateAndSet(JsonWriter::JsonWriterState::EndedArray);

	if (PreviousState != JsonWriter::JsonWriterState::StartedObject && PreviousState != JsonWriter::JsonWriterState::EndedObject &&
		PreviousState != JsonWriter::JsonWriterState::StartedArray && PreviousState != JsonWriter::JsonWriterState::EndedArray)
	{
		WriteString(Environment::NewLine());
		for (uint16_t i = 0; i < _Depth - 1; i++)
		{
			WriteIndent();
		}
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
	JsonWriter::JsonWriterState PreviousState = _State;
	ValidateAndSet(JsonWriter::JsonWriterState::PropertyName);
	if (PreviousState == JsonWriter::JsonWriterState::StartedObject)
	{
		WriteString(Environment::NewLine());
	}
	else if (PreviousState == JsonWriter::JsonWriterState::PropertyValue || PreviousState == JsonWriter::JsonWriterState::EndedObject || 
		PreviousState == JsonWriter::JsonWriterState::EndedArray)
	{
#ifdef UNICODE
		WriteString(L',');
#else
		WriteString(',');
#endif
		WriteString(Environment::NewLine());
	}
	for (uint16_t i = 0; i < _Depth; i++)
	{
		WriteIndent();
	}
#ifdef UNICODE
	WriteString(L'"');
#else
	WriteString('"');
#endif
	WriteEscapedString(Name);
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
	PrepareWritingValue();
#ifdef UNICODE
	WriteString(Value ? L"true" : L"false");
#else
	WriteString(Value ? "true" : "false");
#endif
}
void Elysium::Core::Json::JsonWriter::WriteValue(const int & Value)
{
	PrepareWritingValue();
#ifdef UNICODE
	WriteString(std::to_wstring(Value).c_str());
#else
	WriteString(std::to_string(Value).c_str());
#endif
}
void Elysium::Core::Json::JsonWriter::WriteValue(const float & Value)
{
	PrepareWritingValue();
#ifdef UNICODE
	WriteString(std::to_wstring(Value).c_str());
#else
	WriteString(std::to_string(Value).c_str());
#endif
}
void Elysium::Core::Json::JsonWriter::WriteValue(const double & Value)
{
	PrepareWritingValue();
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
	PrepareWritingValue();
#ifdef UNICODE
	WriteString(L'"');
#else
	WriteString('"');
#endif
	WriteEscapedString(Value);
#ifdef UNICODE
	WriteString(L'"');
#else
	WriteString('"');
#endif
}

void Elysium::Core::Json::JsonWriter::WriteNull()
{
	PrepareWritingValue();
#ifdef UNICODE
	WriteString(L"null");
#else
	WriteString("null");
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

void Elysium::Core::Json::JsonWriter::PrepareWritingValue()
{
	if (_State == JsonWriter::JsonWriterState::PropertyName)
	{
		WriteIndentSpace();
	}
	else if (_State == JsonWriter::JsonWriterState::StartedArray)
	{
		WriteString(Environment::NewLine());
		for (uint16_t i = 0; i < _Depth; i++)
		{
			WriteIndent();
		}
	}
	else if (_State == JsonWriter::JsonWriterState::PropertyValue)
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
	ValidateAndSet(JsonWriter::JsonWriterState::PropertyValue);
}
void Elysium::Core::Json::JsonWriter::ValidateAndSet(JsonWriter::JsonWriterState AspiredState)
{
	JsonWriter::JsonWriterState NextState = _StateLookupTable[(uint32_t)_State][(uint32_t)AspiredState];
	if (NextState == JsonWriter::JsonWriterState::Error)
	{
		throw JsonWriterException();
	}

	_State = AspiredState;
}

void Elysium::Core::Json::JsonWriter::WriteEscapedString(const String & Value)
{
	const size_t ValueLength = Value.GetLength();
	for (int i = 0; i < ValueLength; i++)
	{
		switch (Value[i])
		{
		case L'"':
			WriteString(L"\\\\\\\"");
			break;
		case L'\\':
			WriteString(L"\\\\");
			break;
		case L'\b':
			WriteString(L"\\\\b");
			break;
		case L'\f':
			WriteString(L"\\\\f");
			break;
		case L'\n':
			WriteString(L"\\\\n");
			break;
		case L'\r':
			WriteString(L"\\\\r");
			break;
		case L'\t':
			WriteString(L"\\\\t");
			break;
		default:
			if (Value[i] >= 0x00 && Value[i] <= 0x1F)
			{
				// ToDo:!!!
			}
			else
			{
				WriteString(Value[i]);
			}
			break;
		}
	}
}
