/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_IO_DEVICE_FILEDEVICE
#define ELYSIUM_CORE_TEMPLATE_IO_DEVICE_FILEDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_IOEXCEPTION
#include "../../Exceptions/IO/IOException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEACCESS
#include "../FileAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEMODE
#include "../FileMode.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILEOPTIONS
#include "../FileOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_IO_FILESHARE
#include "../FileShare.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MEMORY_MEMCPY
#include "../../Memory/MemCpy.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../../Text/String.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../../Text/Unicode/Utf16.hpp"
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#elif defined ELYSIUM_CORE_OS_ANDROID

#else
#error "undefined os"
#endif

namespace Elysium::Core::Template::IO::Device
{
	class FileDevice
	{
	public:
		constexpr FileDevice() noexcept = delete;

		inline constexpr FileDevice(const char8_t* FQFN, const FileMode Mode, const FileAccess Access = FileAccess::Read | FileAccess::Write, const FileShare Share = FileShare::None,
			const Elysium::Core::uint32_t BufferSize = 4096, const FileOptions Options = FileOptions::None) noexcept
			: _FQFN(FQFN), _FileHandle(CreateNativeFileHandle(_FQFN, Mode, Access, Share, Options))
		{ }

		constexpr FileDevice(const FileDevice& Source) = delete;

		constexpr FileDevice(FileDevice&& Right) noexcept = delete;

		inline ~FileDevice()
		{
			Flush();
			Close();
		}
	public:
		constexpr FileDevice& operator=(const FileDevice& Source) = delete;

		constexpr FileDevice& operator=(FileDevice&& Right) noexcept = delete;
	public:
		inline constexpr const bool operator==(const FileDevice& Other) noexcept
		{
			return &_FQFN == &Other._FQFN;
		}
	public:
		inline constexpr const Elysium::Core::Template::System::size GetLength() const
		{
			LARGE_INTEGER Size;
			if (!GetFileSizeEx(_FileHandle, &Size))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			return Size.QuadPart;
		}

		inline constexpr const Elysium::Core::Template::System::uint64_t GetPosition() const
		{
			return _Position;
		}
	public:
		inline void SetPosition(const Elysium::Core::Template::System::uint64_t Position)
		{
			//Seek(Position, SeekOrigin::Begin);
			_Position = Position;
		}
	public:
		inline void Close()
		{
			if (INVALID_HANDLE_VALUE == _FileHandle)
			{
				return;
			}

			if (!CloseHandle(_FileHandle))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			_FileHandle = INVALID_HANDLE_VALUE;
		}
	public:
		inline const Elysium::Core::Template::System::size Read(Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				//return 0;
				throw 1;
				//throw ArgumentNullException(u8"Buffer");
			}

			Elysium::Core::uint32_t BytesRead = 0;
			if (!ReadFile(_FileHandle, Buffer, static_cast<DWORD>(Count), (unsigned long*)&BytesRead, nullptr))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}
			_Position += BytesRead;

			return BytesRead;
		}
	public:
		inline void Write(const Elysium::Core::Template::System::byte* Buffer, const Elysium::Core::Template::System::size Count)
		{
			if (nullptr == Buffer || 0 == Count)
			{
				return;
				//throw ArgumentNullException(u8"Buffer");
			}
			/*
			if (Buffer == nullptr)
			{
				throw 1;
				//throw ArgumentNullException(u8"Buffer");
			}

			if (Count == 0)
			{
				return;
			}
			*/
			Elysium::Core::uint32_t TotalBytesWritten = 0;
			Elysium::Core::uint32_t BytesWritten = 0;
			do
			{
				if (!WriteFile(_FileHandle, &Buffer[TotalBytesWritten], static_cast<unsigned long>(Count - TotalBytesWritten), (unsigned long*)&BytesWritten, nullptr))
				{
					throw Elysium::Core::Template::Exceptions::IO::IOException();
				}
				TotalBytesWritten += BytesWritten;
				_Position += BytesWritten;
			} while (TotalBytesWritten != Count);
		}

		inline void Flush(const bool FlushToDisk = true)
		{
			if (!FlushToDisk)
			{
				return;
			}

			if (!FlushFileBuffers(_FileHandle))
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}
		}
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline HANDLE CreateNativeFileHandle(const Elysium::Core::Template::Text::String<char8_t>& FQFN, const FileMode Mode, const FileAccess Access, const FileShare Share,
			const FileOptions Options)
		{
			Elysium::Core::Template::Text::String<wchar_t> WindowsFQPN = Elysium::Core::Template::Text::Unicode::Utf16::SafeToWideString(&FQFN[0], FQFN.GetLength());


			HANDLE NativeFileHandle = CreateFile(&WindowsFQPN[0], static_cast<Elysium::Core::uint32_t>(Access), static_cast<Elysium::Core::uint32_t>(Share),
				nullptr, // default security
				static_cast<Elysium::Core::uint32_t>(Mode), static_cast<Elysium::Core::int32_t>(Options), nullptr);
			//CreateFile2()

			if (INVALID_HANDLE_VALUE == NativeFileHandle)
			{
				throw Elysium::Core::Template::Exceptions::IO::IOException();
			}

			return NativeFileHandle;
		}
#endif
	private:
		Elysium::Core::Template::Text::String<char8_t> _FQFN;
		Elysium::Core::Template::System::size _Position;

#if defined ELYSIUM_CORE_OS_WINDOWS
		HANDLE _FileHandle;
#endif
	};
}
#endif
