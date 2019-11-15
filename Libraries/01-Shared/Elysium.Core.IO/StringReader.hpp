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

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			class ELYSIUM_CORE_API StringReader : public TextReader
			{
			public:
				StringReader(String& Input);
				~StringReader();

				virtual int Peek() override;

				virtual int Read() override;

				virtual StringView ReadLine() override;

				virtual StringView ReadToEnd() override;
			private:
				size_t _Position;
				String& _Input;
			};
		}
	}
}
#endif
