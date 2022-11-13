#include "JsonWriter.hpp"

#ifndef ELYSIUM_CORE_BOOLEAN
#include "../Elysium.Core/Boolean.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Convert.hpp"
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
/*EndedObject*/		{ JsonWriterState::Error,	JsonWriterState::StartedObject,		JsonWriterState::EndedObject,	JsonWriterState::Error,			JsonWriterState::EndedArray,	JsonWriterState::PropertyName,		JsonWriterState::Error,			JsonWriterState::Finished,	JsonWriterState::Error },
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
		WriteString(u8',');
	}

	if (_Depth > 0 && PreviousState != JsonWriter::JsonWriterState::StartedArray)
	{
		WriteIndentSpace();
	}
	WriteString(u8'{');
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
		WriteString(_IOSettings._NewLine);
		for (uint16_t i = 0; i < _Depth - 1; i++)
		{
			WriteIndent();
		}
	}
	WriteString(u8'}');
	_Depth--;
}

void Elysium::Core::Json::JsonWriter::WriteStartArray()
{
	JsonWriter::JsonWriterState PreviousState = _State;
	ValidateAndSet(JsonWriter::JsonWriterState::StartedArray);
	if (PreviousState == JsonWriter::JsonWriterState::EndedArray)
	{
		WriteString(u8',');
	}

	if (PreviousState != JsonWriter::JsonWriterState::Initialized && PreviousState != JsonWriter::JsonWriterState::StartedArray)
	{
		WriteIndentSpace();
	}
	WriteString(u8'[');
	_Depth++;
}
void Elysium::Core::Json::JsonWriter::WriteEndArray()
{
	JsonWriter::JsonWriterState PreviousState = _State;
	ValidateAndSet(JsonWriter::JsonWriterState::EndedArray);

	if (PreviousState != JsonWriter::JsonWriterState::StartedObject && PreviousState != JsonWriter::JsonWriterState::EndedObject &&
		PreviousState != JsonWriter::JsonWriterState::StartedArray && PreviousState != JsonWriter::JsonWriterState::EndedArray)
	{
		WriteString(_IOSettings._NewLine);
		for (uint16_t i = 0; i < _Depth - 1; i++)
		{
			WriteIndent();
		}
	}
	WriteString(u8']');
	_Depth--;
}

void Elysium::Core::Json::JsonWriter::WritePropertyName(const Utf8String& Name)
{
	JsonWriter::JsonWriterState PreviousState = _State;
	ValidateAndSet(JsonWriter::JsonWriterState::PropertyName);
	if (PreviousState == JsonWriter::JsonWriterState::StartedObject)
	{
		WriteString(_IOSettings._NewLine);
	}
	else if (PreviousState == JsonWriter::JsonWriterState::PropertyValue || PreviousState == JsonWriter::JsonWriterState::EndedObject || 
		PreviousState == JsonWriter::JsonWriterState::EndedArray)
	{
		WriteString(u8',');
		WriteString(_IOSettings._NewLine);
	}
	for (uint16_t i = 0; i < _Depth; i++)
	{
		WriteIndent();
	}
	WriteString(u8'"');
	WriteEscapedString(Name);
	WriteString(u8'"');
	WriteString(u8':');
}

void Elysium::Core::Json::JsonWriter::WriteValue(const bool Value)
{
	PrepareWritingValue();
	WriteString(Value ? Elysium::Core::Boolean::TrueString : Elysium::Core::Boolean::FalseString);
}
void Elysium::Core::Json::JsonWriter::WriteValue(const int Value)
{
	PrepareWritingValue();
	WriteString(Template::Text::Convert<char8_t>::ToString(Value, 10));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const float Value)
{
	PrepareWritingValue();
	WriteString(Template::Text::Convert<char8_t>::ToString(Value, 10));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const double Value)
{
	PrepareWritingValue();
	WriteString(Template::Text::Convert<char8_t>::ToString(Value, 10));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const char8_t * Value)
{
	WriteValue(Utf8String(Value));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const Utf8String& Value)
{
	PrepareWritingValue();
	WriteString(u8'"');
	WriteEscapedString(Value);
	WriteString(u8'"');
}

void Elysium::Core::Json::JsonWriter::WriteNull()
{
	PrepareWritingValue();
	WriteString(u8"null");
}

Elysium::Core::Json::JsonWriter::JsonWriter(const JsonIOSettings& IOSettings)
	: _State(JsonWriter::JsonWriterState::Initialized), _Depth(0), _IOSettings(JsonIOSettings(IOSettings))
{
}

void Elysium::Core::Json::JsonWriter::WriteIndent()
{
	WriteString(_IOSettings._Indent);
}
void Elysium::Core::Json::JsonWriter::WriteIndentSpace()
{
	WriteString(_IOSettings._IndentSpace);
}
void Elysium::Core::Json::JsonWriter::WriteValueDelimiter()
{
	WriteString(u8',');
}

void Elysium::Core::Json::JsonWriter::PrepareWritingValue()
{
	if (_State == JsonWriter::JsonWriterState::PropertyName)
	{
		WriteIndentSpace();
	}
	else if (_State == JsonWriter::JsonWriterState::StartedArray)
	{
		WriteString(_IOSettings._NewLine);
		for (uint16_t i = 0; i < _Depth; i++)
		{
			WriteIndent();
		}
	}
	else if (_State == JsonWriter::JsonWriterState::PropertyValue)
	{
		WriteString(u8',');
		WriteString(_IOSettings._NewLine);
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

void Elysium::Core::Json::JsonWriter::WriteEscapedString(const Utf8String& Value)
{
	const Elysium::Core::size ValueLength = Value.GetLength();
	for (int i = 0; i < ValueLength; i++)
	{
		switch (Value[i])
		{
		case u8'\x00':
			WriteString(u8"\\u0000");
			break;
		case u8'\x01':
			WriteString(u8"\\u0001");
			break;
		case u8'\x02':
			WriteString(u8"\\u0002");
			break;
		case u8'\x03':
			WriteString(u8"\\u0003");
			break;
		case u8'\x04':
			WriteString(u8"\\u0004");
			break;
		case u8'\x05':
			WriteString(u8"\\u0005");
			break;
		case u8'\x06':
			WriteString(u8"\\u0006");
			break;
		case u8'\x07':
			WriteString(u8"\\u0007");
			break;
		case u8'\x08':	// \b
			WriteString(u8"\\\\b");
			break;
		case u8'\x09':	// \t
			WriteString(u8"\\\\t");
			break;
		case u8'\x0A':	// \n
			WriteString(u8"\\\\n");
			break;
		case u8'\x0B':
			WriteString(u8"\\u0011");
			break;
		case u8'\x0C':	// \f
			WriteString(u8"\\\\f");
			break;
		case u8'\x0D':	// \r
			WriteString(u8"\\\\r");
			break;
		case u8'\x0E':
			WriteString(u8"\\u0014");
			break;
		case u8'\x0F':
			WriteString(u8"\\u0015");
			break;
		case u8'\x10':
			WriteString(u8"\\u0016");
			break;
		case u8'\x11':
			WriteString(u8"\\u0017");
			break;
		case u8'\x12':
			WriteString(u8"\\u0018");
			break;
		case u8'\x13':
			WriteString(u8"\\u0019");
			break;
		case u8'\x14':
			WriteString(u8"\\u0020");
			break;
		case u8'\x15':
			WriteString(u8"\\u0021");
			break;
		case u8'\x16':
			WriteString(u8"\\u0022");
			break;
		case u8'\x17':
			WriteString(u8"\\u0023");
			break;
		case u8'\x18':
			WriteString(u8"\\u0024");
			break;
		case u8'\x19':
			WriteString(u8"\\u0025");
			break;
		case u8'\x1A':
			WriteString(u8"\\u0026");
			break;
		case u8'\x1B':
			WriteString(u8"\\u0027");
			break;
		case u8'\x1C':
			WriteString(u8"\\u0028");
			break;
		case u8'\x1D':
			WriteString(u8"\\u0029");
			break;
		case u8'\x1E':
			WriteString(u8"\\u0030");
			break;
		case u8'\x1F':
			WriteString(u8"\\u0031");
			break;
		case u8'\x22':	// \"
			WriteString(u8"\\\\\\\"");
			break;
		case u8'\x5C':	// backslash
			WriteString(u8"\\\\\\\\");
			break;
		default:
			WriteString(Value[i]);
			break;
		}
	}
}
