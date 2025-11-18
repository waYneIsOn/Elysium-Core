#include "NamedPipeServerStream.hpp"

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "../Elysium.Core.IO/IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Elysium.Core.Template/Utf16.hpp"
#endif

Elysium::Core::IO::Pipes::NamedPipeServerStream::NamedPipeServerStream(Elysium::Core::Utf8String::ConstCharacterPointer PipeName, const PipeDirection Direction, const Elysium::Core::Template::System::uint8_t MaxNumberOfServerInstances, const PipeTransmissionMode TransmissionMode, const PipeOptions Options, const Elysium::Core::Template::System::size InBufferSize, const Elysium::Core::Template::System::size OutBufferSize)
	: Elysium::Core::IO::Pipes::PipeStream(Direction, TransmissionMode, OutBufferSize),
	_NativeNamedPipeHandle(CreateNativeNamedPipeHandle(BuildFQPipeName(PipeName), Direction, MaxNumberOfServerInstances, TransmissionMode,
	Options, InBufferSize, OutBufferSize, static_cast<PipeAccessRights>(0))), _Options(Options)
{ }

Elysium::Core::IO::Pipes::NamedPipeServerStream::~NamedPipeServerStream() noexcept
{
	Close();
}

void Elysium::Core::IO::Pipes::NamedPipeServerStream::WaitForConnection()
{
	BOOL Result = ConnectNamedPipe(_NativeNamedPipeHandle, nullptr);
	if (FALSE == Result)
	{
		const DWORD LastError = GetLastError();
		switch (LastError)
		{
		case ERROR_PIPE_CONNECTED:
			// This happens if a client has connected before the server called ConnectNamedPipe(...) which is ok.
			break;
		case ERROR_NO_DATA:
			// This happens if a client connects and immedtiately closes the connection.
			// The pipe is essentially "damaged" at this point.
			Disconnect();

			break;
		default:
			throw IOException(LastError);
		}
	}
}

void Elysium::Core::IO::Pipes::NamedPipeServerStream::Disconnect()
{
	if (INVALID_HANDLE_VALUE != _NativeNamedPipeHandle)
	{
		DisconnectNamedPipe(_NativeNamedPipeHandle);
	}
}

void Elysium::Core::IO::Pipes::NamedPipeServerStream::Close()
{
	if (INVALID_HANDLE_VALUE != _NativeNamedPipeHandle)
	{
		//DisconnectNamedPipe(_NativeNamedPipeHandle);
		CloseHandle(_NativeNamedPipeHandle);
		_NativeNamedPipeHandle = INVALID_HANDLE_VALUE;
	}
}

void Elysium::Core::IO::Pipes::NamedPipeServerStream::Flush()
{
}

const Elysium::Core::size Elysium::Core::IO::Pipes::NamedPipeServerStream::Seek(const Elysium::Core::int64_t Offset, const Elysium::Core::IO::SeekOrigin Origin)
{
	return Elysium::Core::size();
}

const Elysium::Core::size Elysium::Core::IO::Pipes::NamedPipeServerStream::Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
{
	DWORD BytesRead;
	BOOL Result = ReadFile(_NativeNamedPipeHandle, Buffer, Count, &BytesRead, nullptr);
	if (FALSE == Result)
	{
		throw IOException();
	}

	return static_cast<Elysium::Core::size>(BytesRead);
}

Elysium::Core::byte Elysium::Core::IO::Pipes::NamedPipeServerStream::ReadByte()
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

void Elysium::Core::IO::Pipes::NamedPipeServerStream::Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count)
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

Elysium::Core::Utf8String Elysium::Core::IO::Pipes::NamedPipeServerStream::BuildFQPipeName(Elysium::Core::Utf8String::ConstCharacterPointer PipeName)
{
	static constexpr const Elysium::Core::Template::System::size FixedLength = 13; // \\\\.\\pipe\\ + PipeName

	const Elysium::Core::Template::System::size PipeNameLength =
		Elysium::Core::Template::Text::CharacterTraits<char8_t>::GetLength(PipeName);

	// @ToDo: validate and append (instead of doing it this way ^^)
	Elysium::Core::Template::System::size CurrentIndex = 0;
	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(FixedLength + PipeNameLength);
	Result[CurrentIndex] = u8'\\';
	Result[++CurrentIndex] = u8'\\';
	Result[++CurrentIndex] = u8'.';
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

HANDLE Elysium::Core::IO::Pipes::NamedPipeServerStream::CreateNativeNamedPipeHandle(const Elysium::Core::Utf8String& PipeName, const PipeDirection Direction, const Elysium::Core::Template::System::uint8_t MaxNumberOfServerInstances, const PipeTransmissionMode TransmissionMode, const PipeOptions Options, const Elysium::Core::Template::System::size InBufferSize, const Elysium::Core::Template::System::size OutBufferSize, const PipeAccessRights AdditionalAccessRights)
{
	// https://learn.microsoft.com/en-us/windows/win32/ipc/named-pipes
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createnamedpipea

	// @ToDo: don't assume correct input (Utf16::SafeToWideString)
	Elysium::Core::WideString WindowsPath = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&PipeName[0],
		PipeName.GetLength());

	DWORD OpenMode = static_cast<DWORD>(Direction) | (MaxNumberOfServerInstances == 1 ? FILE_FLAG_FIRST_PIPE_INSTANCE : 0) |
		static_cast<DWORD>(Options) | static_cast<DWORD>(AdditionalAccessRights);
	DWORD PipeMode = static_cast<DWORD>(TransmissionMode) << 2 | static_cast<DWORD>(TransmissionMode) << 1;

	// https://learn.microsoft.com/en-us/windows/win32/api/wtypesbase/ns-wtypesbase-security_attributes
	// ToDo: lpSecurityDescriptor and bInheritHandle
	SECURITY_ATTRIBUTES SecurityAttributes = SECURITY_ATTRIBUTES();
	SecurityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	SecurityAttributes.lpSecurityDescriptor = nullptr;
	SecurityAttributes.bInheritHandle = FALSE;

	HANDLE NativeNamedPipeHandle = CreateNamedPipeW(&WindowsPath[0], OpenMode, PipeMode, MaxNumberOfServerInstances,
		OutBufferSize, InBufferSize, NMPWAIT_USE_DEFAULT_WAIT, &SecurityAttributes);
	if (INVALID_HANDLE_VALUE == NativeNamedPipeHandle)
	{
		throw IOException();
	}

	return NativeNamedPipeHandle;
}
