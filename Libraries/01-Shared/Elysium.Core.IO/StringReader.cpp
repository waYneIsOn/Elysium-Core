#include "StringReader.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

Elysium::Core::IO::StringReader::StringReader(const String & Input)
	: Elysium::Core::IO::TextReader(),
	_Input(Input)
{ }
Elysium::Core::IO::StringReader::~StringReader()
{ }

const Elysium::Core::uint8_t Elysium::Core::IO::StringReader::Peek()
{
	return _Position < _Input.GetLength() ? _Input[_Position] : -1;
}

const Elysium::Core::uint8_t Elysium::Core::IO::StringReader::Read()
{
	return _Position < _Input.GetLength() ? _Input[_Position++] : -1;
}

Elysium::Core::String Elysium::Core::IO::StringReader::ReadLine()
{
	if (_Position == _Input.GetLength())
	{
		return String();
	}

	size_t IndexOfNewLine = _Input.IndexOf(Elysium::Core::Environment::NewLine(), _Position);
	if (IndexOfNewLine == -1)
	{
		size_t Position = _Position;
		_Position = _Input.GetLength();
		return String(&_Input[Position]);
	}
	else
	{
		size_t Position = _Position;
		_Position += IndexOfNewLine + Elysium::Core::Environment::NewLine().GetLength();
		return String(&_Input[Position], IndexOfNewLine);
	}
}

Elysium::Core::String Elysium::Core::IO::StringReader::ReadToEnd()
{
	return String(&_Input[_Position], _Input.GetLength() - _Position);
}
