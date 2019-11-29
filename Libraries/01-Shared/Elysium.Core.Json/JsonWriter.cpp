#include "JsonWriter.hpp"

#ifndef ELYSIUM_CORE_CONVERT
#include "../Elysium.Core/Convert.hpp"
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
		WriteString(u',');
	}

	if (_Depth > 0 && PreviousState != JsonWriter::JsonWriterState::StartedArray)
	{
		WriteIndentSpace();
	}
	WriteString(u'{');
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
	WriteString(u'}');
	_Depth--;
}

void Elysium::Core::Json::JsonWriter::WriteStartArray()
{
	JsonWriter::JsonWriterState PreviousState = _State;
	ValidateAndSet(JsonWriter::JsonWriterState::StartedArray);
	if (PreviousState == JsonWriter::JsonWriterState::EndedArray)
	{
		WriteString(u',');
	}

	if (PreviousState != JsonWriter::JsonWriterState::Initialized && PreviousState != JsonWriter::JsonWriterState::StartedArray)
	{
		WriteIndentSpace();
	}
	WriteString(u'[');
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
	WriteString(u']');
	_Depth--;
}

void Elysium::Core::Json::JsonWriter::WritePropertyName(const String & Name)
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
		WriteString(u',');
		WriteString(_IOSettings._NewLine);
	}
	for (uint16_t i = 0; i < _Depth; i++)
	{
		WriteIndent();
	}
	WriteString(u'"');
	WriteEscapedString(Name);
	WriteString(u'"');
	WriteString(u':');
}

void Elysium::Core::Json::JsonWriter::WriteValue(const bool & Value)
{
	PrepareWritingValue();
	WriteString(Value ? u"true" : u"false");
}
void Elysium::Core::Json::JsonWriter::WriteValue(const int & Value)
{
	PrepareWritingValue();
	WriteString(Convert::ToString(Value, 10));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const float & Value)
{
	PrepareWritingValue();
	WriteString(Convert::ToString(Value, 10));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const double & Value)
{
	PrepareWritingValue();
	WriteString(Convert::ToString(Value, 10));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const char16_t * Value)
{
	WriteValue(String(Value));
}
void Elysium::Core::Json::JsonWriter::WriteValue(const String & Value)
{
	PrepareWritingValue();
	WriteString(u'"');
	WriteEscapedString(Value);
	WriteString(u'"');
}

void Elysium::Core::Json::JsonWriter::WriteNull()
{
	PrepareWritingValue();
	WriteString(u"null");
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
	WriteString(u',');
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
		WriteString(u',');
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

void Elysium::Core::Json::JsonWriter::WriteEscapedString(const String & Value)
{
	const size_t ValueLength = Value.GetLength();
	for (int i = 0; i < ValueLength; i++)
	{
		switch (Value[i])
		{
		case u'\x00':
			WriteString(u"\\u0000");
			break;
		case u'\x01':
			WriteString(u"\\u0001");
			break;
		case u'\x02':
			WriteString(u"\\u0002");
			break;
		case u'\x03':
			WriteString(u"\\u0003");
			break;
		case u'\x04':
			WriteString(u"\\u0004");
			break;
		case u'\x05':
			WriteString(u"\\u0005");
			break;
		case u'\x06':
			WriteString(u"\\u0006");
			break;
		case u'\x07':
			WriteString(u"\\u0007");
			break;
		case u'\x08':	// \b
			WriteString(u"\\\\b");
			break;
		case u'\x09':	// \t
			WriteString(u"\\\\t");
			break;
		case u'\x0A':	// \n
			WriteString(u"\\\\n");
			break;
		case u'\x0B':
			WriteString(u"\\u0011");
			break;
		case u'\x0C':	// \f
			WriteString(u"\\\\f");
			break;
		case u'\x0D':	// \r
			WriteString(u"\\\\r");
			break;
		case u'\x0E':
			WriteString(u"\\u0014");
			break;
		case u'\x0F':
			WriteString(u"\\u0015");
			break;
		case u'\x10':
			WriteString(u"\\u0016");
			break;
		case u'\x11':
			WriteString(u"\\u0017");
			break;
		case u'\x12':
			WriteString(u"\\u0018");
			break;
		case u'\x13':
			WriteString(u"\\u0019");
			break;
		case u'\x14':
			WriteString(u"\\u0020");
			break;
		case u'\x15':
			WriteString(u"\\u0021");
			break;
		case u'\x16':
			WriteString(u"\\u0022");
			break;
		case u'\x17':
			WriteString(u"\\u0023");
			break;
		case u'\x18':
			WriteString(u"\\u0024");
			break;
		case u'\x19':
			WriteString(u"\\u0025");
			break;
		case u'\x1A':
			WriteString(u"\\u0026");
			break;
		case u'\x1B':
			WriteString(u"\\u0027");
			break;
		case u'\x1C':
			WriteString(u"\\u0028");
			break;
		case u'\x1D':
			WriteString(u"\\u0029");
			break;
		case u'\x1E':
			WriteString(u"\\u0030");
			break;
		case u'\x1F':
			WriteString(u"\\u0031");
			break;
		case u'\x22':	// \"
			WriteString(u"\\\\\\\"");
			break;
		case u'\x5C':	// backslash
			WriteString(u"\\\\\\\\");
			break;
		default:
			WriteString(Value[i]);
			break;
		}
	}
}
