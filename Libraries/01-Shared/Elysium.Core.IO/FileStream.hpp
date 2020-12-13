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

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEACCESS
#include "FileAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEMODE
#include "FileMode.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESHARE
#include "FileShare.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEOPTIONS
#include "FileOptions.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _APISETHANDLE_
#include <handleapi.h>
#endif

#ifndef _APISETFILE_
#include <fileapi.h>
#endif

#ifndef ELYSIUM_CORE_TEXT_UTF16ENCODING
#include "../Elysium.Core.Text/UTF16Encoding.hpp"
#endif

#elif defined(__ANDROID__)

#else
#error "undefined os"
#endif

#pragma warning(disable : 4251)	// disable warning about str::string and std::fstream

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API FileStream : public Stream
	{
	public:
		FileStream(const String& Path, const FileMode Mode);
		FileStream(const String& Path, const FileMode Mode, const FileAccess Access);
		FileStream(const String& Path, const FileMode Mode, const FileAccess Access, const FileShare Share);
		FileStream(const String& Path, const FileMode Mode, const FileAccess Access, const FileShare Share, const Elysium::Core::uint32_t BufferSize, const FileOptions Options);
		FileStream(const FileStream& Source) = delete;
		FileStream(FileStream&& Right) noexcept = delete;
		virtual ~FileStream();

		FileStream& operator=(const FileStream& Source) = delete;
		FileStream& operator=(FileStream&& Right) noexcept = delete;

		// properties - getter
		virtual const bool GetCanRead() const override;
		virtual const bool GetCanSeek() const override;
		virtual const bool GetCanTimeout() const override;
		virtual const bool GetCanWrite() const override;

		virtual const size_t GetLength() const override;
		virtual const Elysium::Core::int64_t GetPosition() const override;
		virtual const Elysium::Core::int32_t GetReadTimeout() const override;
		virtual const Elysium::Core::int32_t GetWriteTimeout() const override;

		// properties - setter
		virtual void SetLength(const size_t Value) override;
		virtual void SetPosition(const Elysium::Core::int64_t Position) override;
		virtual void SetReadTimeout(const Elysium::Core::int32_t Value) override;
		virtual void SetWriteTimeout(const Elysium::Core::int32_t Value) override;

		// methods
		virtual void Close() override;
		virtual void Flush() override;
		virtual void Flush(const bool FlushToDisk);
		virtual void Seek(const Elysium::Core::int64_t Offset, const SeekOrigin Origin) override;
		virtual const size_t Read(Elysium::Core::byte* Buffer, const size_t Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const Elysium::Core::byte* Buffer, const size_t Count) override;
	private:
		const String _Path;

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
		const Elysium::Core::Text::UTF16Encoding _WindowsEncoding = Elysium::Core::Text::UTF16Encoding();

		HANDLE _FileHandle;
#elif defined(__ANDROID__)

#else

#endif

		static constexpr const Elysium::Core::uint32_t DefaultBufferSize = 4096;
	};
}
#endif
