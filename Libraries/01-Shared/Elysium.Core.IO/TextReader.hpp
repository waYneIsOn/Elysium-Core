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

#ifndef ELYSIUM_CORE_DECIMAL
#include "../Elysium.Core/Decimal.hpp"
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

				virtual int Peek();

				virtual int Read();
				//virtual int Reader(array<char>& Buffer, int Index, int Count);

				//virtual String ReadLine();

				//virtual String ReadToEnd();
			protected:
				TextReader();
			};
		}
	}
}
#endif
