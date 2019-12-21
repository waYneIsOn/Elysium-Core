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

namespace Elysium::Core::Text
{
	class ELYSIUM_CORE_API UTF8Encoding final : public Encoding
	{
	public:
		UTF8Encoding();
		UTF8Encoding(bool EncoderShouldEmitUTF8Identifier);
		~UTF8Encoding();
	private:
		bool _EncoderShouldEmitUTF8Identifier;
	};
}
#endif
