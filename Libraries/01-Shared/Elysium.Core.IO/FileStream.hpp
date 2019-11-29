/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#define ELYSIUM_CORE_IO_FILESTREAM

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

#ifndef _STDINT_H
#include <cstdint>
#endif

#ifndef _FSTREAM_
#include <fstream>
#endif

#pragma warning(disable : 4251)	// disable warning about str::string and std::fstream

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			class ELYSIUM_CORE_API FileStream : public Stream
			{
			public:
				FileStream(const String& Path, FileMode Mode);
				FileStream(const String& Path, FileMode Mode, FileAccess Access);
				FileStream(const String& Path, FileMode Mode, FileAccess Access, FileShare Share);
				~FileStream();

				// properties - getter
				virtual bool GetCanRead() const override;
				virtual bool GetCanSeek() const override;
				virtual bool GetCanTimeout() const override;
				virtual bool GetCanWrite() const override;

				virtual size_t GetLength() override;
				virtual int64_t GetPosition() override;
				virtual int GetReadTimeout() const override;
				virtual int GetWriteTimeout() const override;

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
				virtual void Write(const byte* Buffer, const size_t Count) override;
			private:
				String _Path;
				FileMode _Mode;
				FileAccess _Access;
				FileShare _Share;

				//std::basic_fstream<char16_t> _NativeStream;
				std::fstream _NativeStream;

				//std::fstream::_Openmode Convert(FileMode Mode, FileAccess Access, FileShare Share);
			};
		}
	}
}
#endif
