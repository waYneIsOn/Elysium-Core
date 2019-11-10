/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_STREAMREADER
#define ELYSIUM_CORE_IO_STREAMREADER

#ifndef ELYSIUM_CORE_IO_TEXTREADER
#include "TextReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "Stream.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			class ELYSIUM_CORE_API StreamReader : public TextReader
			{
			public:
				StreamReader(Stream& InputStream);
				~StreamReader();

				virtual void Close() override;

				virtual int Peek() override;
			private:
				Stream& _InputStream;
			};
		}
	}
}
#endif
