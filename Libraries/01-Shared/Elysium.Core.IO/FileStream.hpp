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

#ifndef ELYSIUM_CORE_IO_FILEACCESS
#include "FileAccess.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILEMODE
#include "FileMode.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESHARE
#include "FileShare.hpp"
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
			class EXPORT FileStream : public Stream
			{
			public:
				FileStream(std::wstring Path, FileMode Mode, FileAccess Access, FileShare Share);
				~FileStream();

				// properties - getter
				virtual bool GetCanRead() const override;
				virtual bool GetCanSeek() const override;
				virtual bool GetCanTimeout() const override;
				virtual bool GetCanWrite() const override;

				virtual size_t GetLength() const override;
				virtual __int64 GetPosition() const override;
				virtual int GetReadTimeout() const override;
				virtual int GetWriteTimeout() const override;

				// properties - setter
				virtual void SetLength(size_t Value) override;
				virtual void SetPosition(__int64 Position) override;
				virtual void SetReadTimeout(int Value) override;
				virtual void SetWriteTimeout(int Value) override;

				// methods
				virtual void Close() override;
				virtual void Flush() override;
				virtual void Seek(const __int64 Offset, const SeekOrigin Origin) override;
				virtual int Read(byte* Buffer, const int Offset, const int Count) override;
				virtual void Write(const byte* Buffer, const int Offset, const int Count) override;
			private:
				std::wstring _Path;
				FileMode _Mode;
				FileAccess _Access;
				FileShare _Share;

				std::fstream _NativeStream;

				//std::fstream::_Openmode Convert(FileMode Mode, FileAccess Access, FileShare Share);
			};
		}
	}
}
#endif
