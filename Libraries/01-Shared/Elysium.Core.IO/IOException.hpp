/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_IOEXCEPTION
#define ELYSIUM_CORE_IO_IOEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API IOException : public SystemException
	{
	public:
		IOException();
		IOException(const char8_t* Message);
		IOException(String&& Message);
		virtual ~IOException();
	};
}
#endif
