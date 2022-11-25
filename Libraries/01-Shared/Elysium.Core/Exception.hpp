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
		Exception();

		Exception(Elysium::Core::Utf8String::ConstCharacterPointer Message);

		Exception(Elysium::Core::Utf8String&& Message);

		//Exception(const Exception& Source) = delete;

		//Exception(Exception&& Right) noexcept = delete;

		virtual ~Exception();
	public:
		//Exception& operator=(const Exception& Source) = delete;

		//Exception& operator=(Exception&& Right) noexcept = delete;
	public:
		const Elysium::Core::Utf8String& GetExceptionMessage() const;
	private:
		Elysium::Core::Utf8String _Message;
	};
}
#endif
