/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_TEXT_ASCIIENCODING
#define ELYSIUM_CORE_TEXT_ASCIIENCODING

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "Encoding.hpp"
#endif

namespace Elysium::Core::Text
{
	class ELYSIUM_CORE_API ASCIIEncoding final : public Encoding
	{
	public:
		ASCIIEncoding();
		~ASCIIEncoding();
	};
}
#endif
