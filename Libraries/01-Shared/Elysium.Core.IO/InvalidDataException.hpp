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
#include "../Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API InvalidDataException : public Exception
	{
	public:
		InvalidDataException();

		InvalidDataException(const char8_t* Message);

		InvalidDataException(Elysium::Core::Utf8String&& Message);

		InvalidDataException(const InvalidDataException& Source);

		virtual ~InvalidDataException();
	};
}
#endif
