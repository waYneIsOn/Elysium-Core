/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_TEXT_UTF8ENCODING
#define ELYSIUM_CORE_TEXT_UTF8ENCODING

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "Encoding.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Text
		{
			class EXPORT UTF8Encoding : public Encoding
			{
			public:
				UTF8Encoding();
				UTF8Encoding(bool EncoderShouldEmitUTF8Identifier);
				~UTF8Encoding();
			private:
				bool _EncoderShouldEmitUTF8Identifier;
			};
		}
	}
}
#endif
