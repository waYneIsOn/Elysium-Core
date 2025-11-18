#include "NamedPipeClientStream.hpp"

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "../Elysium.Core.IO/IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Elysium.Core.Template/Utf16.hpp"
#endif

Elysium::Core::IO::Pipes::NamedPipeClientStream::NamedPipeClientStream(Elysium::Core::Utf8String::ConstCharacterPointer PipeName, Elysium::Core::Utf8String::ConstCharacterPointer ServerName, const PipeDirection Direction, const PipeOptions Options, Elysium::Core::Security::Principal::TokenImpersonationLevel ImpersonationLevel, Elysium::Core::IO::HandleInheritability Inheritability)
	: Elysium::Core::IO::Pipes::PipeStream(Direction, PipeTransmissionMode::Byte, 0),
	_FQPipeName(BuildFQPipeName(PipeName, ServerName)), _NativeNamedPipeHandle(INVALID_HANDLE_VALUE)
{ }

Elysium::Core::IO::Pipes::NamedPipeClientStream::~NamedPipeClientStream() noexcept
{
	Close();
}

void Elysium::Core::IO::Pipes::NamedPipeClientStream::Connect(const TimeSpan Timeout)
{
	Close();

	// @ToDo: don't assume correct input (Utf16::SafeToWideString)
	Elysium::Core::WideString WindowsPath = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&_FQPipeName[0],
		_FQPipeName.GetLength());

	// @ToDo: only run until defined timeout
	do
	{
		HANDLE NativeNamedPipeHandle = CreateFileW(&WindowsPath[0], GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (INVALID_HANDLE_VALUE == NativeNamedPipeHandle)
		{
			//throw IOException();
			continue;
		}

		_NativeNamedPipeHandle = NativeNamedPipeHandle;
		break;
	} while (true);
}

void Elysium::Core::IO::Pipes::NamedPipeClientStream::Close()
{
	if (INVALID_HANDLE_VALUE != _NativeNamedPipeHandle)
	{
		CloseHandle(_NativeNamedPipeHandle);
		_NativeNamedPipeHandle = INVALID_HANDLE_VALUE;
	}
}

void Elysium::Core::IO::Pipes::NamedPipeClientStream::Flush()
{
}

const Elysium::Core::size Elysium::Core::IO::Pipes::NamedPipeClientStream::Seek(const Elysium::Core::int64_t Offset, const Elysium::Core::IO::SeekOrigin Origin)
{
	return 0;
}

const Elysium::Core::size Elysium::Core::IO::Pipes::NamedPipeClientStream::Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
{
	DWORD BytesRead;
	BOOL Result = ReadFile(_NativeNamedPipeHandle, Buffer, Count, &BytesRead, nullptr);
	if (FALSE == Result)
	{
		throw IOException();
	}

	return static_cast<Elysium::Core::size>(BytesRead);
}

Elysium::Core::byte Elysium::Core::IO::Pipes::NamedPipeClientStream::ReadByte()
{
	Elysium::Core::byte Data = 0x00;

	DWORD BytesRead;
	BOOL Result = ReadFile(_NativeNamedPipeHandle, &Data, sizeof(Elysium::Core::byte), &BytesRead, nullptr);
	if (FALSE == Result)
	{
		throw IOException();
	}

	return Data;
}

void Elysium::Core::IO::Pipes::NamedPipeClientStream::Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
{
	DWORD TotalBytesWritten = 0;
	do
	{
		DWORD BytesWritten;
		BOOL Result = WriteFile(_NativeNamedPipeHandle, &Buffer[TotalBytesWritten], Count - TotalBytesWritten, &BytesWritten, nullptr);
		if (FALSE == Result)
		{
			throw IOException();
		}

		TotalBytesWritten += BytesWritten;
	} while (TotalBytesWritten < Count);
}

Elysium::Core::Utf8String Elysium::Core::IO::Pipes::NamedPipeClientStream::BuildFQPipeName(Elysium::Core::Utf8String::ConstCharacterPointer PipeName, Elysium::Core::Utf8String::ConstCharacterPointer ServerName)
{
	static constexpr const Elysium::Core::Template::System::size FixedLength = 12; // \\\\ + ServerName + \\pipe\\ + PipeName

	const Elysium::Core::Template::System::size PipeNameLength = 
		Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(PipeName);
	const Elysium::Core::Template::System::size ServerNameLength =
		Elysium::Core::Template::Text::CharacterTraits<Elysium::Core::Utf8String::Character>::GetLength(ServerName);

	// @ToDo: validate and append (instead of doing it this way ^^)
	Elysium::Core::Template::System::size CurrentIndex = 0;
	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(FixedLength + PipeNameLength + ServerNameLength);
	Result[CurrentIndex] = u8'\\';
	Result[++CurrentIndex] = u8'\\';
	for (Elysium::Core::Template::System::size i = 0; i < ServerNameLength; ++i)
	{
		Result[++CurrentIndex] = ServerName[i];
	}
	Result[++CurrentIndex] = u8'\\';
	Result[++CurrentIndex] = u8'p';
	Result[++CurrentIndex] = u8'i';
	Result[++CurrentIndex] = u8'p';
	Result[++CurrentIndex] = u8'e';
	Result[++CurrentIndex] = u8'\\';
	for (Elysium::Core::Template::System::size i = 0; i < PipeNameLength; ++i)
	{
		Result[++CurrentIndex] = PipeName[i];
	}

	return Result;
}
