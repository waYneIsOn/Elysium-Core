#include "StringReader.hpp"

#ifndef ELYSIUM_CORE_ENVIRONMENT
#include "../Elysium.Core/Environment.hpp"
#endif

Elysium::Core::IO::StringReader::StringReader(const Elysium::Core::Utf8String& Input)
	: Elysium::Core::IO::TextReader(),
	_Input(&Input[0])
{ }

Elysium::Core::IO::StringReader::~StringReader()
{ }

const Elysium::Core::uint32_t Elysium::Core::IO::StringReader::Peek()
{
	return _Position < _Input.GetLength() ? _Input[_Position] : -1;
}

const Elysium::Core::uint32_t Elysium::Core::IO::StringReader::Read()
{
	return _Position < _Input.GetLength() ? _Input[_Position++] : -1;
}

const Elysium::Core::size Elysium::Core::IO::StringReader::Read(char8_t* Buffer, const Elysium::Core::size Count)
{
	// ToDo:
	throw 1;
}

Elysium::Core::Utf8String Elysium::Core::IO::StringReader::ReadLine()
{
	if (_Position == _Input.GetLength())
	{
		return Elysium::Core::Utf8String();
	}

	Elysium::Core::size IndexOfNewLine = _Input.IndexOf(&Elysium::Core::Environment::NewLine[0], _Position);
	if (IndexOfNewLine == -1)
	{
		Elysium::Core::size Position = _Position;
		_Position = _Input.GetLength();
		return Elysium::Core::Utf8String(&_Input[Position]);
	}
	else
	{
		Elysium::Core::size Position = _Position;
		_Position += IndexOfNewLine + Elysium::Core::Environment::NewLine.GetLength();
		return Elysium::Core::Utf8String(&_Input[Position], IndexOfNewLine);
	}
}

Elysium::Core::Utf8String Elysium::Core::IO::StringReader::ReadToEnd()
{
	return Elysium::Core::Utf8String(&_Input[_Position], _Input.GetLength() - _Position);
}
