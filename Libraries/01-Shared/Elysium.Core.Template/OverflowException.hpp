/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OVERFLOWEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OVERFLOWEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARITHMETICEXCEPTION
#include "ArithmeticException.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

namespace Elysium::Core::Template::Exceptions
{
	/// <summary>
	/// The exception that is thrown when an arithmetic, casting, or conversion operation in a checked context results in an overflow.
	/// </summary>
	class OverflowException : public ArithmeticException
	{
	public:
		OverflowException();

		OverflowException(const char8_t* Message);

		OverflowException(Text::String<char8_t>&& Message);

		virtual ~OverflowException();
	};

	inline Elysium::Core::Template::Exceptions::OverflowException::OverflowException()
		: Elysium::Core::Template::Exceptions::ArithmeticException(u8"OverflowException")
	{ }

	inline Elysium::Core::Template::Exceptions::OverflowException::OverflowException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::ArithmeticException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::OverflowException::OverflowException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::ArithmeticException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::OverflowException::~OverflowException()
	{ }
}
#endif
