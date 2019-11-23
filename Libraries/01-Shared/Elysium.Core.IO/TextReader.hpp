/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_TEXTREADER
#define ELYSIUM_CORE_IO_TEXTREADER

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_DECIMAL
#include "../Elysium.Core/Decimal.hpp"
#endif

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			class ELYSIUM_CORE_API TextReader
			{
			public:
				virtual ~TextReader();

				virtual void Close();

				virtual const int32_t Peek();

				virtual const int32_t Read();
				//virtual int Read(array<char>& Buffer, int Index, int Count);
				//virtual int Read(String& Buffer, int Index, int Count);

				virtual StringView ReadLine() = 0;

				virtual StringView ReadToEnd() = 0;
			protected:
				TextReader();
			};
		}
	}
}
#endif
