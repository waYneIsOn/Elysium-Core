#include "JsonReader.hpp"

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
const Elysium::Core::String & Elysium::Core::Json::JsonReader::GetNodeValue() const
{
	return _CurrentNodeValue;
}

bool Elysium::Core::Json::JsonReader::Read()
{
	switch (_State)
	{
	case Elysium::Core::Json::JsonReader::JsonReaderState::Initialized:
	case Elysium::Core::Json::JsonReader::JsonReaderState::StartedObject:
	case Elysium::Core::Json::JsonReader::JsonReaderState::EndedObject:
	case Elysium::Core::Json::JsonReader::JsonReaderState::StartedArray:
	case Elysium::Core::Json::JsonReader::JsonReaderState::EndedArray:
	case Elysium::Core::Json::JsonReader::JsonReaderState::PropertyName:
	case Elysium::Core::Json::JsonReader::JsonReaderState::InBetweenValues:
		while (true)
		{
			const int32_t CurrentCharacter = ReadNextCharacterFromSource();
			switch (CurrentCharacter)
			{
			case u8'{':
				_State = JsonReader::JsonReaderState::StartedObject;
				_CurrentToken = JsonToken::StartedObject;
				return true;
			case u8'}':
				_State = JsonReader::JsonReaderState::EndedObject;
				_CurrentToken = JsonToken::EndedObject;
				return true;
			case u8'[':
				_State = JsonReader::JsonReaderState::StartedArray;
				_CurrentToken = JsonToken::StartedArray;
				return true;
			case u8']':
				_State = JsonReader::JsonReaderState::EndedArray;
				_CurrentToken = JsonToken::EndedArray;
				return true;
			case -1:	// end of source
				_State = JsonReader::JsonReaderState::Finished;
				_CurrentToken = JsonToken::None;
				return false;
			case u8' ':
			case u8',':
			case u8'\r':
			case u8'\n':
			case u8'\t':
				break;
			case u8'"':
				// don't set the either _State or _CurrentToken here since we don't know whether we're reading a property name or value yet
				return ReadProperty();
			case u8'-':
			case u8'1':
			case u8'2':
			case u8'3':
			case u8'4':
			case u8'5':
			case u8'6':
			case u8'7':
			case u8'8':
			case u8'9':
				_State = JsonReader::JsonReaderState::PropertyValue;
				_CurrentToken = JsonToken::Integer;
				return ReadValueNumeric(CurrentCharacter);
			case u8't':
			case u8'f':
				_State = JsonReader::JsonReaderState::PropertyValue;
				_CurrentToken = JsonToken::Boolean;
				return ReadValueBool(CurrentCharacter);
			case u8'n':
				_State = JsonReader::JsonReaderState::PropertyValue;
				_CurrentToken = JsonToken::Null;
				return ReadValueNull(CurrentCharacter);
			default:
				// ToDo: message
				throw JsonReaderException();
			}
		}
	case Elysium::Core::Json::JsonReader::JsonReaderState::Finished:
		throw JsonReaderException(u8"reader has already finished");
	case Elysium::Core::Json::JsonReader::JsonReaderState::Error:
		throw JsonReaderException(u8"reader has already encountered an error");
	default:
		// ToDo: message
		throw JsonReaderException();
	}
}

Elysium::Core::Json::JsonReader::JsonReader(const JsonIOSettings& IOSettings)
	: _IOSettings(IOSettings), _State(JsonReader::JsonReaderState::Initialized), _CurrentToken(JsonToken::None), _CurrentNodeValue(), _PropertyBuffer()
{
}

bool Elysium::Core::Json::JsonReader::ReadProperty()
{
	// buffer property name
	char16_t PreviousCharacter;
	int32_t CurrentCharacter;
	while(true)
	{
		CurrentCharacter = ReadNextCharacterFromSource();
		if (CurrentCharacter == -1)
		{
			return false;
		}
		if (CurrentCharacter == u8'"' && PreviousCharacter != u8'\\')
		{
			break;
		}
		_PropertyBuffer.Append(CurrentCharacter);
		PreviousCharacter = CurrentCharacter;
	}

	// eat indent so we can check whether we've just read a property name or value
	EatIndent();
	const int32_t NextCharacter = PeekNextCharacterFromSource();
	if (NextCharacter == u8':')
	{
		ReadNextCharacterFromSource();

		_State = JsonReader::JsonReaderState::PropertyName;
		_CurrentToken = JsonToken::PropertyName;
		_CurrentNodeValue = _PropertyBuffer.ToString();
		_PropertyBuffer.Clear();
		return true;
	}
	else if (NextCharacter == u8',' || NextCharacter == u8'}' || NextCharacter == u8']')
	{
		_State = JsonReader::JsonReaderState::InBetweenValues;
		_CurrentToken = JsonToken::String;
		_CurrentNodeValue = _PropertyBuffer.ToString();
		_PropertyBuffer.Clear();
		return true;
	}
	else
	{
		// ToDo:
		throw JsonReaderException(u8"unexpected character xy in line ....");
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
		case u8',':
		case u8'\r':
		case u8'\n':
			_State = JsonReader::JsonReaderState::InBetweenValues;
			_CurrentNodeValue = ValueBuilder.ToString();
			return true;
		case u8'.':
			_CurrentToken = JsonToken::Float;
		case u8'0':
		case u8'1':
		case u8'2':
		case u8'3':
		case u8'4':
		case u8'5':
		case u8'6':
		case u8'7':
		case u8'8':
		case u8'9':
			ValueBuilder.Append(CurrentCharacter);
			break;
		default:
			// ToDo:
			_State = JsonReader::JsonReaderState::Error;
			throw JsonReaderException(u8"unexpected character xy in line ....");
		}
	}
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
		case u8',':
		case u8'\r':
		case u8'\n':
			_State = JsonReader::JsonReaderState::InBetweenValues;
			_CurrentNodeValue = ValueBuilder.ToString();
			return true;
		case u8'r':
		case u8'u':
		case u8'e':
		case u8'a':
		case u8'l':
		case u8's':
			ValueBuilder.Append(CurrentCharacter);
			break;
		default:
			// ToDo:
			_State = JsonReader::JsonReaderState::Error;
			throw JsonReaderException(u8"unexpected character xy in line ....");
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
		case u8',':
		case u8'\r':
		case u8'\n':
			_State = JsonReader::JsonReaderState::InBetweenValues;
			_CurrentNodeValue = ValueBuilder.ToString();
			return true;
		case u8'u':
		case u8'l':
			ValueBuilder.Append(CurrentCharacter);
			break;
		default:
			// ToDo:
			_State = JsonReader::JsonReaderState::Error;
			throw JsonReaderException(u8"unexpected character xy in line ....");
		}
	}
}

void Elysium::Core::Json::JsonReader::EatIndent()
{
	// eat any indent
	while (true)
	{
		switch (PeekNextCharacterFromSource())
		{
		case u8' ':
		case u8'\r':
		case u8'\n':
		case u8'\t':
			ReadNextCharacterFromSource();
			break;
		default:
			return;
		}
	}
}
