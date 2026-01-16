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

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEMEXCEPTION
#include "../Elysium.Core/SystemException.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API IOException 
		: public SystemException
	{
	public:
		IOException();

		IOException(const char8_t* Message);

		IOException(Elysium::Core::Utf8String&& Message);

		IOException(const Elysium::Core::Template::System::uint32_t ErrorCode);

		virtual ~IOException() = default;
	};
}
#endif
