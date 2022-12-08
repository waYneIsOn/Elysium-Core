/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_DIVIDEBYZEROEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_DIVIDEBYZEROEXCEPTION

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
	/// The exception that is thrown when there is an attempt to divide an integral or Decimal value by zero.
	/// </summary>
	class DivideByZeroException : public ArithmeticException
	{
	public:
		DivideByZeroException();

		DivideByZeroException(const char8_t* Message);

		DivideByZeroException(Text::String<char8_t>&& Message);

		virtual ~DivideByZeroException();
	};

	inline Elysium::Core::Template::Exceptions::DivideByZeroException::DivideByZeroException()
		: Elysium::Core::Template::Exceptions::ArithmeticException(u8"DivideByZeroException")
	{ }

	inline Elysium::Core::Template::Exceptions::DivideByZeroException::DivideByZeroException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::ArithmeticException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::DivideByZeroException::DivideByZeroException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::ArithmeticException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::DivideByZeroException::~DivideByZeroException()
	{ }
}
#endif
