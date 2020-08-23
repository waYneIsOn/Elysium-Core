/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef _FSTREAM_
#include <fstream>
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
		FileStream(const FileStream& Source) = delete;
		FileStream(FileStream&& Right) noexcept = delete;
		virtual ~FileStream();

		FileStream& operator=(const FileStream& Source) = delete;
		FileStream& operator=(FileStream&& Right) noexcept = delete;

		// properties - getter
		virtual bool GetCanRead() const override;
		virtual bool GetCanSeek() const override;
		virtual bool GetCanTimeout() const override;
		virtual bool GetCanWrite() const override;

		virtual const size_t GetLength() override;
		virtual const int64_t GetPosition() override;
		virtual const int GetReadTimeout() const override;
		virtual const int GetWriteTimeout() const override;

		// properties - setter
		virtual void SetLength(size_t Value) override;
		virtual void SetPosition(int64_t Position) override;
		virtual void SetReadTimeout(int Value) override;
		virtual void SetWriteTimeout(int Value) override;

		// methods
		virtual void Close() override;
		virtual void Flush() override;
		virtual void Seek(const int64_t Offset, const SeekOrigin Origin) override;
		virtual size_t Read(byte* Buffer, const size_t Count) override;
		virtual Elysium::Core::byte ReadByte() override;
		virtual void Write(const byte* Buffer, const size_t Count) override;
	private:
		String _Path;

		//std::basic_fstream<char16_t> _NativeStream;
		std::fstream _NativeStream;

		//std::fstream::_Openmode Convert(FileMode Mode, FileAccess Access, FileShare Share);
	};
}
#endif
