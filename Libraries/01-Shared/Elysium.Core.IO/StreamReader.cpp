#include "StreamReader.hpp"

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
#endif

Elysium::Core::IO::StreamReader::StreamReader(Stream & InputStream, const Text::Encoding& Encoding, const bool DetecEncodingFromByteOrderMarks, const Elysium::Core::int32_t MinimumBufferSize, const bool LeaveOpen)
	: Elysium::Core::IO::TextReader(),
	_InputStream(InputStream), _Encoding(Encoding), _LeaveOpen(LeaveOpen), 
	_Buffer(Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(DefaultBufferSize)), _BufferPosition(0)
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

const Elysium::Core::int32_t Elysium::Core::IO::StreamReader::Peek()
{	// ToDo: can we actually peek?
	Elysium::Core::byte Result = _InputStream.ReadByte();
	_InputStream.SetPosition(_InputStream.GetPosition() - 1);

	return Result;
}

const Elysium::Core::int32_t Elysium::Core::IO::StreamReader::Read()
{
	return _InputStream.ReadByte();
}

const Elysium::Core::int32_t Elysium::Core::IO::StreamReader::Read(char8_t* Buffer, const Elysium::Core::int32_t Count)
{
	if (_InputStream.GetPosition() == 0)
	{
		const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> BOM = _Encoding.GetPreamble();
		const size_t BOMLength = BOM.GetLength();
		if (BOMLength > 0)
		{

		}
	}

	const size_t BytesRead = _InputStream.Read(&_Buffer[0], _Buffer.GetLength());

	/*
	Elysium::Core::Collections::Template::List<Elysium::Core::byte> LocalBuffer = Elysium::Core::Collections::Template::List<Elysium::Core::byte>(Count);
	const size_t BytesRead = _InputStream.Read(&LocalBuffer[0], Count);

	// ...

	return BytesRead;
	*/
	throw NotImplementedException();
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
