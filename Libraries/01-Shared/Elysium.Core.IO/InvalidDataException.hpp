/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION
#define ELYSIUM_CORE_IO_INVALIDDATAEXCEPTION

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
	class ELYSIUM_CORE_API InvalidDataException : public Exception
	{
	public:
		InvalidDataException();
		InvalidDataException(const char8_t* Message);
		InvalidDataException(String&& Message);
		virtual ~InvalidDataException();
	};
}
#endif
