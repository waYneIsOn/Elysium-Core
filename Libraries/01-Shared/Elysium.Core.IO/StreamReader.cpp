#include "StreamReader.hpp"

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::IO::StreamReader::StreamReader(Stream & InputStream, Text::Encoding& Encoding, const bool DetectEncodingFromByteOrderMarks, const Elysium::Core::int32_t MinimumBufferSize, const bool LeaveOpen)
	: Elysium::Core::IO::TextReader(),
	_InputStream(InputStream), _Encoding(Encoding), _DetectEncoding(DetectEncodingFromByteOrderMarks), _LeaveOpen(LeaveOpen),
	_Buffer(Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(MinimumBufferSize == -1 ? DefaultBufferSize : MinimumBufferSize)),
	_BufferWritingPosition(0), _BufferReadingPosition(0)
{ }
Elysium::Core::IO::StreamReader::~StreamReader()
{
	if (!_LeaveOpen)
	{
		Close();
	}
}

void Elysium::Core::IO::StreamReader::Close()
{
	_InputStream.Close();
}

const Elysium::Core::uint32_t Elysium::Core::IO::StreamReader::Peek()
{	// ToDo: can we actually peek?
	Elysium::Core::byte Result = _InputStream.ReadByte();
	_InputStream.SetPosition(_InputStream.GetPosition() - 1);

	return Result;
}

const Elysium::Core::uint32_t Elysium::Core::IO::StreamReader::Read()
{
	if (_BufferReadingPosition == 0)
	{
		FillBuffer(_Buffer.GetLength());
	}

	throw 1;
	//return _InputStream.ReadByte();
}

const Elysium::Core::size Elysium::Core::IO::StreamReader::Read(char8_t* Buffer, const Elysium::Core::size Count)
{
	const Elysium::Core::size InternalBufferSize = _Buffer.GetLength();
	if (Count > InternalBufferSize)
	{	// in this case it makes sense to read directly into user-provided-buffer (ToDo: performance tests!)
		if (_BufferReadingPosition < _BufferWritingPosition)
		{	// there still is buffered data available ergo return before working with stream
			const Elysium::Core::size BytesCopyable = InternalBufferSize - _BufferReadingPosition;
			memcpy(Buffer, &_Buffer[_BufferReadingPosition], BytesCopyable);
			_BufferReadingPosition = 0;
			return BytesCopyable;
		}

		return _InputStream.Read((Elysium::Core::byte*)Buffer, Count);
		//return PopulateBuffer(Buffer, Count);
	}
	else
	{
		if (_BufferReadingPosition >= _BufferWritingPosition)
		{
			FillBuffer(InternalBufferSize);
		}

		const Elysium::Core::size BytesCopyable = InternalBufferSize - _BufferReadingPosition;
		memcpy(Buffer, &_Buffer[_BufferReadingPosition], BytesCopyable);

		_BufferReadingPosition += BytesCopyable;
		if (_BufferReadingPosition >= InternalBufferSize)
		{
			_BufferReadingPosition = -1;
		}

		return BytesCopyable;
	}
}

Elysium::Core::String Elysium::Core::IO::StreamReader::ReadLine()
{
	Elysium::Core::Text::StringBuilder Builder = Elysium::Core::Text::StringBuilder();

	throw NotImplementedException();
}

Elysium::Core::String Elysium::Core::IO::StreamReader::ReadToEnd()
{
	Elysium::Core::Text::StringBuilder Builder = Elysium::Core::Text::StringBuilder();

	throw NotImplementedException();
}

void Elysium::Core::IO::StreamReader::FillBuffer(const Elysium::Core::size Count)
{
	_BufferWritingPosition = 0;
	do
	{
		const Elysium::Core::size BytesRead = _InputStream.Read(&_Buffer[_BufferWritingPosition], Count - _BufferWritingPosition);
		if (BytesRead == 0)
		{
			break;
		}
		_BufferWritingPosition += BytesRead;
	} while (_BufferWritingPosition < Count);

	_BufferReadingPosition = 0;

	if (_DetectEncoding)
	{
		DetectEncoding();
	}
}

void Elysium::Core::IO::StreamReader::DetectEncoding()
{
	// as UTF32 is the one encoding with the largest BOM I'm trying to guess/detect, I need at least four bytes to be available
	if (_BufferWritingPosition < 4)
	{
		return;
	}
	_DetectEncoding = false;

	if (_Buffer[0] == 0xFE && _Buffer[1] == 0xFF)
	{
		_BufferReadingPosition += 2;
		//_Encoding = Elysium::Core::Text::Encoding::UTF16BE();
	}
	else if (_Buffer[0] == 0xFF && _Buffer[1] == 0xFE)
	{
		if (_Buffer[2] == 0x00 && _Buffer[3] == 0x00)
		{	// UTF32 LE
			_BufferReadingPosition += 2;
		}
		else
		{	// UTF16 LE
			_BufferReadingPosition += 2;
		}
	}
	else if (_Buffer[0] == 0x00 && _Buffer[1] == 0x00 && _Buffer[2] == 0xFE && _Buffer[3] == 0xFF)
	{	// UTF32 BE
		_BufferReadingPosition += 4;
	}
	else if (_Buffer[0] == 0xEF && _Buffer[1] == 0xBB && _Buffer[2] == 0xBF)
	{	// UTF-8
		_BufferReadingPosition += 3;

	}
	/*
	else if (_Buffer[0] == 0x2B && _Buffer[1] == 0x2F && _Buffer[2] == 0x76)
	{	// UTF-7
		_BufferReadingPosition += 3;

	}
	else if (_Buffer[0] == 0xF7 && _Buffer[1] == 0x64 && _Buffer[2] == 0x4C)
	{	// UTF-1
		_BufferReadingPosition += 3;

	}
	else if (...)
	{	// ...

	}
	*/

	// ToDo:
	throw 1;
}
