/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_INTERNALBUFFEROVERFLOWEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_IO_INTERNALBUFFEROVERFLOWEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "../SystemException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../Primitives.hpp"
#endif

namespace Elysium::Core::Template::Exceptions::IO
{
	class InternalBufferOverflowException
		: public SystemException
	{
	public:
		constexpr InternalBufferOverflowException() = delete;

		constexpr InternalBufferOverflowException(const System::uint32_t ErrorCode, const char8_t* Message = nullptr);

		constexpr InternalBufferOverflowException(const InternalBufferOverflowException& Source) = delete;

		constexpr InternalBufferOverflowException(InternalBufferOverflowException&& Right) noexcept;

		constexpr virtual ~InternalBufferOverflowException() override = default;
	public:
		constexpr InternalBufferOverflowException& operator=(const InternalBufferOverflowException& Source) = delete;

		constexpr InternalBufferOverflowException& operator=(InternalBufferOverflowException&& Right) noexcept;
	};
	
	inline constexpr InternalBufferOverflowException::InternalBufferOverflowException(const System::uint32_t ErrorCode, const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException::SystemException(ErrorCode, Message)
	{ }

	inline constexpr InternalBufferOverflowException::InternalBufferOverflowException(InternalBufferOverflowException&& Right) noexcept
		: Elysium::Core::Template::Exceptions::SystemException::SystemException(Elysium::Core::Template::Functional::Move(Right))
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	inline constexpr InternalBufferOverflowException& InternalBufferOverflowException::operator=(InternalBufferOverflowException&& Right) noexcept
	{
		//Elysium::Core::Template::Exceptions::SystemException::operator=(Right);
		return *this;
	}
}
#endif
