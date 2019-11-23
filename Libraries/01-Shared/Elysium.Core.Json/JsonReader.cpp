#include "JsonReader.hpp"

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#include "JsonReaderException.hpp"
#endif

Elysium::Core::Json::JsonReader::~JsonReader()
{
}

const Elysium::Core::Json::JsonToken Elysium::Core::Json::JsonReader::GetToken() const
{
	return _CurrentToken;
}
const Elysium::Core::String & Elysium::Core::Json::JsonReader::GetNodeName() const
{
	return _CurrentNodeName;
}
const Elysium::Core::String & Elysium::Core::Json::JsonReader::GetNodeValue() const
{
	return _CurrentNodeValue;
}

bool Elysium::Core::Json::JsonReader::Read()
{
	while (true)
	{
		switch (_State)
		{
		case Elysium::Core::Json::JsonReader::JsonReaderState::Initialized:
		case Elysium::Core::Json::JsonReader::JsonReaderState::StartedObject:
		case Elysium::Core::Json::JsonReader::JsonReaderState::EndedObject:
		case Elysium::Core::Json::JsonReader::JsonReaderState::StartedArray:
		case Elysium::Core::Json::JsonReader::JsonReaderState::EndedArray:
			return ReadDocument();
			/*
		case Elysium::Core::Json::JsonReader::JsonReaderState::PropertyName:
			break;
		case Elysium::Core::Json::JsonReader::JsonReaderState::PropertyValue:
			break;
			*/
		case Elysium::Core::Json::JsonReader::JsonReaderState::InBetweenValues:
			return ReadDocument();
		case Elysium::Core::Json::JsonReader::JsonReaderState::Finished:
			throw JsonReaderException(L"reader has already finished");
		case Elysium::Core::Json::JsonReader::JsonReaderState::Error:
			throw JsonReaderException(L"reader has already encountered an error");
		default:
			// ToDo: message
			throw JsonReaderException();
		}
	}
}

Elysium::Core::Json::JsonReader::JsonReader(const JsonIOSettings& IOSettings)
	: _IOSettings(IOSettings), _State(JsonReader::JsonReaderState::Initialized), _CurrentToken(JsonToken::None), _CurrentNodeName(), _CurrentNodeValue()
{
}

bool Elysium::Core::Json::JsonReader::ReadDocument()
{
	while (true)
	{
		const int32_t CurrentCharacter = ReadNextCharacterFromSource();
		switch (CurrentCharacter)
		{
		case L'{':
			_State = JsonReader::JsonReaderState::StartedObject;
			_CurrentToken = JsonToken::StartedObject;
			return true;
		case L'}':
			_State = JsonReader::JsonReaderState::EndedObject;
			_CurrentToken = JsonToken::EndedObject;
			return true;
		case L'[':
			_State = JsonReader::JsonReaderState::StartedArray;
			_CurrentToken = JsonToken::StartedArray;
			return true;
		case L']':
			_State = JsonReader::JsonReaderState::EndedArray;
			_CurrentToken = JsonToken::EndedArray;
			return true;
		case -1:	// end of source
			_State = JsonReader::JsonReaderState::Finished;
			_CurrentToken = JsonToken::None;
			return false;
		case L' ':
		case L',':
		case L'\r':
		case L'\n':
		case L'\t':
			break;
		case L'"':
			_State = JsonReader::JsonReaderState::PropertyValue;
			_CurrentToken = JsonToken::String;
			return ReadValueString();
		case L'1':
		case L'2':
		case L'3':
		case L'4':
		case L'5':
		case L'6':
		case L'7':
		case L'8':
		case L'9':
			_State = JsonReader::JsonReaderState::PropertyValue;
			_CurrentToken = JsonToken::Integer;
			return ReadValueNumeric(CurrentCharacter);
		case L't':
		case L'f':
			_State = JsonReader::JsonReaderState::PropertyValue;
			_CurrentToken = JsonToken::Boolean;
			return ReadValueBool(CurrentCharacter);
		case L'n':
			_State = JsonReader::JsonReaderState::PropertyValue;
			_CurrentToken = JsonToken::Null;
			return ReadValueNull(CurrentCharacter);
			/*
			ToDo:
				objects, array (of array)
			*/
		default:
			// ToDo: message
			throw JsonReaderException();
		}
	}
}


bool Elysium::Core::Json::JsonReader::ReadValueNumeric(const int32_t FirstCharacter)
{
	Elysium::Core::Text::StringBuilder ValueBuilder = Elysium::Core::Text::StringBuilder();
	ValueBuilder.Append(FirstCharacter);
	while (true)
	{
		const int32_t CurrentCharacter = ReadNextCharacterFromSource();
		switch (CurrentCharacter)
		{
		case L',':
		case L'\r':
		case L'\n':
			_State = JsonReader::JsonReaderState::InBetweenValues;
			_CurrentNodeValue = ValueBuilder.ToString();
			return true;
		case L'.':
			_CurrentToken = JsonToken::Float;
		case L'0':
		case L'1':
		case L'2':
		case L'3':
		case L'4':
		case L'5':
		case L'6':
		case L'7':
		case L'8':
		case L'9':
			ValueBuilder.Append(CurrentCharacter);
			break;
		default:
			// ToDo:
			_State = JsonReader::JsonReaderState::Error;
			throw JsonReaderException(L"unexpected character xy in line ....");
		}
	}
}
bool Elysium::Core::Json::JsonReader::ReadValueString()
{
	Elysium::Core::Text::StringBuilder ValueBuilder = Elysium::Core::Text::StringBuilder();
	while (true)
	{
		const int32_t CurrentCharacter = ReadNextCharacterFromSource();
		switch (CurrentCharacter)
		{
		case L'"':
			_State = JsonReader::JsonReaderState::InBetweenValues;
			_CurrentNodeValue = ValueBuilder.ToString();
			return true;
		default:
			ValueBuilder.Append(CurrentCharacter);
			break;
		}
	}

	return false;
}
bool Elysium::Core::Json::JsonReader::ReadValueBool(const int32_t FirstCharacter)
{
	Elysium::Core::Text::StringBuilder ValueBuilder = Elysium::Core::Text::StringBuilder();
	ValueBuilder.Append(FirstCharacter);
	while (true)
	{
		const int32_t CurrentCharacter = ReadNextCharacterFromSource();
		switch (CurrentCharacter)
		{
		case L',':
		case L'\r':
		case L'\n':
			_State = JsonReader::JsonReaderState::InBetweenValues;
			_CurrentNodeValue = ValueBuilder.ToString();
			return true;
		case L'r':
		case L'u':
		case L'e':
		case L'a':
		case L'l':
		case L's':
			ValueBuilder.Append(CurrentCharacter);
			break;
		default:
			// ToDo:
			_State = JsonReader::JsonReaderState::Error;
			throw JsonReaderException(L"unexpected character xy in line ....");
		}
	}
}
bool Elysium::Core::Json::JsonReader::ReadValueNull(const int32_t FirstCharacter)
{
	Elysium::Core::Text::StringBuilder ValueBuilder = Elysium::Core::Text::StringBuilder();
	ValueBuilder.Append(FirstCharacter);
	while (true)
	{
		const int32_t CurrentCharacter = ReadNextCharacterFromSource();
		switch (CurrentCharacter)
		{
		case L',':
		case L'\r':
		case L'\n':
			_State = JsonReader::JsonReaderState::InBetweenValues;
			_CurrentNodeValue = ValueBuilder.ToString();
			return true;
		case L'u':
		case L'l':
			ValueBuilder.Append(CurrentCharacter);
			break;
		default:
			// ToDo:
			_State = JsonReader::JsonReaderState::Error;
			throw JsonReaderException(L"unexpected character xy in line ....");
		}
	}
}
