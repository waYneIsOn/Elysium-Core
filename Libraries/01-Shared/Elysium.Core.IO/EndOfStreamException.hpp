/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_ENDOFSTREAMEXCEPTION
#define ELYSIUM_CORE_IO_ENDOFSTREAMEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "IOException.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API EndOfStreamException : public IOException
	{
	public:
		EndOfStreamException();

		EndOfStreamException(const char8_t* Message);

		EndOfStreamException(Elysium::Core::Utf8String&& Message);

		virtual ~EndOfStreamException();
	};
}
#endif
