/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Exception.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API IOException : public Exception
	{
	public:
		IOException();
		IOException(const char16_t* Message);
		IOException(String&& Message);
		virtual ~IOException();
	};
}
#endif
