/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_STRINGWRITER
#define ELYSIUM_CORE_IO_STRINGWRITER

#ifndef ELYSIUM_CORE_IO_TEXTWRITER
#include "TextWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace IO
		{
			class ELYSIUM_CORE_API StringWriter : public TextWriter
			{
			public:
				StringWriter(Elysium::Core::Text::StringBuilder& StringBuilder);
				~StringWriter();

				virtual void Write(const byte* Value, const size_t Index, const size_t Length) override;
				virtual void Write(const String& Value) override;
			private:
				Elysium::Core::Text::StringBuilder& _StringBuilder;
			};
		}
	}
}
#endif
