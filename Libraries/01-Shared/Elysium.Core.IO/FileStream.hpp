/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_FILESTREAM
#define ELYSIUM_CORE_IO_FILESTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_IASYNCRESULT
#include "../Elysium.Core/IAsyncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEACCESS
#include "FileAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEMODE
#include "FileMode.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEOPTIONS
#include "FileOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESHARE
#include "FileShare.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESTREAMASYNCRESULT
#include "FileStreamAysncResult.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_DELEGATE
#include "../Elysium.Core.Template/Delegate.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF16ENCODING
#include "../Elysium.Core.Text/UTF16Encoding.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _APISETHANDLE_
#include <handleapi.h>
#endif

#ifndef _APISETFILE_
#include <fileapi.h>
#endif
#elif defined ELYSIUM_CORE_OS_ANDROID

#else
#error "undefined os"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API FileStream : public Stream
	{
		friend class FileStreamAsyncResult;
	public:
		FileStream(const char8_t* Path, const FileMode Mode, const FileAccess Access = FileAccess::Read | FileAccess::Write, 
			const FileShare Share = FileShare::None, const Elysium::Core::uint32_t BufferSize = DefaultBufferSize, 
			const FileOptions Options = FileOptions::None);

		FileStream(const Elysium::Core::Utf8String& Path, const FileMode Mode, const FileAccess Access = FileAccess::Read | FileAccess::Write,
			const FileShare Share = FileShare::None, const Elysium::Core::uint32_t BufferSize = DefaultBufferSize,
			const FileOptions Options = FileOptions::None);
		
		FileStream(const FileStream& Source) = delete;

		FileStream(FileStream&& Right) noexcept = delete;

		virtual ~FileStream();
	public:
		FileStream& operator=(const FileStream& Source) = delete;

		FileStream& operator=(FileStream&& Right) noexcept = delete;
	public:
		virtual const bool GetCanRead() const override;

		virtual const bool GetCanSeek() const override;

		virtual const bool GetCanTimeout() const override;

		virtual const bool GetCanWrite() const override;

		virtual const Elysium::Core::size GetLength() const override;

		virtual const Elysium::Core::size GetPosition() const override;

		virtual const Elysium::Core::uint32_t GetReadTimeout() const override;

		virtual const Elysium::Core::uint32_t GetWriteTimeout() const override;

		virtual void SetLength(const Elysium::Core::size Value) override;

		virtual void SetPosition(const Elysium::Core::uint64_t Position) override;

		virtual void SetReadTimeout(const Elysium::Core::uint32_t Value) override;

		virtual void SetWriteTimeout(const Elysium::Core::uint32_t Value) override;
	public:
		virtual void Close() override;

		virtual void Flush() override;

		virtual void Flush(const bool FlushToDisk);

		virtual const Elysium::Core::size Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin) override;

		virtual const Elysium::Core::size Read(Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;

		virtual Elysium::Core::byte ReadByte() override;

		virtual void Write(const Elysium::Core::byte* Buffer, const Elysium::Core::size Count) override;
	public:
		virtual Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginWrite(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size,
			const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State) override;

		virtual void EndWrite(const Elysium::Core::IAsyncResult* AsyncResult) override;

		virtual Elysium::Core::Template::Memory::UniquePointer<Elysium::Core::IAsyncResult> BeginRead(const Elysium::Core::byte* Buffer, const Elysium::Core::size Size,
			const Elysium::Core::Container::DelegateOfVoidConstIASyncResultPointer& Callback, const void* State) override;

		virtual const Elysium::Core::size EndRead(const Elysium::Core::IAsyncResult* AsyncResult) override;
	private:
		static const Elysium::Core::uint32_t DefaultBufferSize = 4096;
	private:
		Elysium::Core::Utf8String _Path;
		Elysium::Core::size _Position = 0;

#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static const Elysium::Core::Text::Encoding& _OperatingSystemEncoding = Elysium::Core::Text::Encoding::UTF16LE();

		HANDLE _FileHandle;
		PTP_IO _CompletionPortHandle;

		static HANDLE CreateNativeFileHandle(const Utf8String& Path, const FileMode Mode, const FileAccess Access, const FileShare Share, const FileOptions Options);

		static void IOCompletionPortCallback(PTP_CALLBACK_INSTANCE Instance, void* Context, void* Overlapped, ULONG IoResult,
			ULONG_PTR NumberOfBytesTransferred, PTP_IO Io);
#elif defined(ELYSIUM_CORE_OS_ANDROID)
		inline static const Elysium::Core::Text::Encoding& _OperatingSystemEncoding = Elysium::Core::Text::Encoding::UTF8();
#else
#error "unsupported os"
#endif
	};
}
#endif
