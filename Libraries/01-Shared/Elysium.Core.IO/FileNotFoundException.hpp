/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_IO_FILENOTFOUNDEXCEPTION
#define ELYSIUM_CORE_IO_FILENOTFOUNDEXCEPTION

#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#include "IOException.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API FileNotFoundException : public IOException
	{
	public:
		FileNotFoundException();
		FileNotFoundException(const char16_t* Message);
		FileNotFoundException(String&& Message);
		virtual ~FileNotFoundException();
	};
}
#endif
