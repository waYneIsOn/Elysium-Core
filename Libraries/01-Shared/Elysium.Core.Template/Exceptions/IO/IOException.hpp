/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_IOEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_IOEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Exceptions::IO
{
	class IOException
		: public SystemException
	{
	public:
		inline constexpr IOException()
			: Elysium::Core::Template::Exceptions::SystemException::SystemException(GetLastError(), nullptr)
		{}

		inline constexpr IOException(const System::uint32_t ErrorCode, const char8_t* Message)
			: Elysium::Core::Template::Exceptions::SystemException::SystemException(ErrorCode, Message)
		{ }

		inline constexpr IOException(const Elysium::Core::Template::System::uint32_t ErrorCode)
			: Elysium::Core::Template::Exceptions::SystemException::SystemException(ErrorCode)
		{ }

		virtual ~IOException() = default;
	public:
		constexpr IOException& operator=(const IOException& Source) = delete;

		//constexpr IOException& operator=(IOException&& Right) noexcept;
	};
}
#endif
