/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_MEMORYSTREAM
#define ELYSIUM_CORE_IO_MEMORYSTREAM

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_LIST
#include "../Elysium.Core/List.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			class EXPORT MemoryStream : public Stream
			{
			public:
				MemoryStream();
				~MemoryStream();

				// properties - getter
				virtual bool GetCanRead() const override;
				virtual bool GetCanSeek() const override;
				virtual bool GetCanTimeout() const override;
				virtual bool GetCanWrite() const override;

				virtual size_t GetLength() const override;
				virtual __int64 GetPosition() const override;
				virtual int GetReadTimeout() const override;
				virtual int GetWriteTimeout() const override;

				virtual size_t GetCapacity() const;

				// properties - setter
				virtual void SetLength(size_t Value) override;
				virtual void SetPosition(__int64 Position) override;

				virtual void SetCapacity(size_t Capacity);

				// methods
				virtual void Close() override;
				virtual void Flush() override;
				virtual void Seek(const __int64 Offset, const SeekOrigin Origin) override;
				virtual int Read(BYTE* Buffer, const int Offset, const int Count) override;
				virtual void Write(const BYTE* Buffer, const int Offset, const int Count) override;
			private:
				Elysium::Core::Collections::Generic::List<BYTE> _Buffer;
				size_t _CurrentPosition = 0;
			};
		}
	}
}
#endif
