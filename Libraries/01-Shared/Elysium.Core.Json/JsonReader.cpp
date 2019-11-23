#include "JsonReader.hpp"

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#include "JsonReaderException.hpp"
#endif

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
			return ReadDocument();
			/*
		case Elysium::Core::Json::JsonReader::JsonReaderState::StartedObject:
			break;
		case Elysium::Core::Json::JsonReader::JsonReaderState::EndedObject:
			break;
			*/
		case Elysium::Core::Json::JsonReader::JsonReaderState::StartedArray:
			return ReadArray();
			/*
		case Elysium::Core::Json::JsonReader::JsonReaderState::EndedArray:
			break;
		case Elysium::Core::Json::JsonReader::JsonReaderState::PropertyName:
			break;
		case Elysium::Core::Json::JsonReader::JsonReaderState::PropertyValue:
			break;
			*/
		case Elysium::Core::Json::JsonReader::JsonReaderState::InBetweenValues:
			return ReadInBetweenValues();
			/*
		case Elysium::Core::Json::JsonReader::JsonReaderState::Finished:
			break;
		case Elysium::Core::Json::JsonReader::JsonReaderState::Error:
			break;
			*/
		default:
			return false;
		}
	}
	// true if the next node was read successfully, false otherwise
	return false;
}

Elysium::Core::Json::JsonReader::JsonReader(const JsonIOSettings& IOSettings)
	: _IOSettings(IOSettings), _State(JsonReader::JsonReaderState::Initialized), _Index(0), _CurrentToken(JsonToken::None), _CurrentNodeName(), _CurrentNodeValue()
{
}

bool Elysium::Core::Json::JsonReader::ReadDocument()
{
	while (true)
	{
		const ElysiumChar CurrentCharacter = GetChar(_Index);
		switch (CurrentCharacter)
		{
		/*
		ToDo (maybe):
			ignore/eat any indent? or would this be an error?
		*/
		case L'{':
			_State = JsonReader::JsonReaderState::StartedObject;
			_CurrentToken = JsonToken::StartedObject;
			_Index++;
			return true;
		case L'[':
			_State = JsonReader::JsonReaderState::StartedArray;
			_CurrentToken = JsonToken::StartedArray;
			_Index++;
			return true;
		default:
			return false;
		}
	}
}

bool Elysium::Core::Json::JsonReader::ReadArray()
{
	while (true)
	{
		const ElysiumChar CurrentCharacter = GetChar(_Index);
		switch (CurrentCharacter)
		{
		case L'\r':
		case L'\n':
		case L'\t':
			_Index++;
			break;
		case L'"':
			_State = JsonReader::JsonReaderState::PropertyValue;
			_CurrentToken = JsonToken::String;
			_Index++;
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
			return true;	// ToDo: return ReadValueInt();
		/*
		ToDo:
			numerics (int and floats), objects, array (of array), bool, null-values
		*/
		default:
			return false;
		}
	}
}

bool Elysium::Core::Json::JsonReader::ReadValueString()
{
	Elysium::Core::Text::StringBuilder ValueBuilder = Elysium::Core::Text::StringBuilder();

	while (true)
	{
		const ElysiumChar CurrentCharacter = GetChar(_Index);
		switch (CurrentCharacter)
		{
		case L'"':
			_State = JsonReader::JsonReaderState::InBetweenValues;
			_CurrentNodeValue = ValueBuilder.ToString();
			_Index++;
			return true;
		default:
			ValueBuilder.Append(CurrentCharacter);
			_Index++;
			break;
		}
	}

	return false;
}

bool Elysium::Core::Json::JsonReader::ReadInBetweenValues()
{
	while (true)
	{
		const ElysiumChar CurrentCharacter = GetChar(_Index);
		switch (CurrentCharacter)
		{
		case L',':
		case L'\r':
		case L'\n':
		case L'\t':
			_Index++;
			break;
		case L']':
			_State = JsonReader::JsonReaderState::EndedArray;
			_CurrentToken = JsonToken::EndedArray;
			return true;
		case L'"':
			_State = JsonReader::JsonReaderState::PropertyValue;
			_CurrentToken = JsonToken::String;
			_Index++;
			return ReadValueString();
		/*
		ToDo:
			numerics (int and floats), objects, array (of array), bool, null-values
		*/
		default:
			return false;
		}
	}
}
