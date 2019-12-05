/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_STRINGREADER
#define ELYSIUM_CORE_IO_STRINGREADER

#ifndef ELYSIUM_CORE_IO_TEXTREADER
#include "TextReader.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			class ELYSIUM_CORE_API StringReader : public TextReader
			{
			public:
				StringReader(const String& Input);
				~StringReader();

				virtual const int32_t Peek() override;

				virtual const int32_t Read() override;

				virtual StringView ReadLine() override;

				virtual StringView ReadToEnd() override;
			private:
				size_t _Position;
				StringView _Input;
			};
		}
	}
}
#endif