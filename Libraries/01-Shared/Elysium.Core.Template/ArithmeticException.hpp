/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARITHMETICEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARITHMETICEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#include "SystemException.hpp"
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
	/// The exception that is thrown for errors in an arithmetic, casting, or conversion operation.
	/// </summary>
	class ArithmeticException : public SystemException
	{
	public:
		ArithmeticException();

		ArithmeticException(const char8_t* Message);

		ArithmeticException(Text::String<char8_t>&& Message);

		virtual ~ArithmeticException();
	};

	inline Elysium::Core::Template::Exceptions::ArithmeticException::ArithmeticException()
		: Elysium::Core::Template::Exceptions::SystemException(u8"ArithmeticException")
	{ }

	inline Elysium::Core::Template::Exceptions::ArithmeticException::ArithmeticException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::ArithmeticException::ArithmeticException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::SystemException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::ArithmeticException::~ArithmeticException()
	{ }
}
#endif
