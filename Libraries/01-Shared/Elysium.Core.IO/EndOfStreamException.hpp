/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
		EndOfStreamException(const char16_t* Message);
		EndOfStreamException(String&& Message);
		virtual ~EndOfStreamException();
	};
}
#endif
