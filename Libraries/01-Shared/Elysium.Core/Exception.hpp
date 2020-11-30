/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_EXCEPTION
#define ELYSIUM_CORE_EXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Exception
	{
	public:
		// constructors & destructor
		Exception();
		Exception(const char8_t* Message);
		Exception(Elysium::Core::String&& Message);
		virtual ~Exception();

		// properties - getter
		const Exception* GetInnerException() const;

		// methods
		const Elysium::Core::String& GetExceptionMessage() const;
	private:
		Elysium::Core::String _Message;
		Exception* _InnerException;
	};
}
#endif
