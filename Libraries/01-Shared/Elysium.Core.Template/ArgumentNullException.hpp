/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTNULLEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTNULLEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTEXCEPTION
#include "ArgumentException.hpp"
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
	/// The exception that is thrown when one of the arguments provided to a method is not valid.
	/// </summary>
	class ArgumentNullException : public ArgumentException
	{
	public:
		ArgumentNullException();

		ArgumentNullException(const char8_t* Message);

		ArgumentNullException(Text::String<char8_t>&& Message);

		virtual ~ArgumentNullException();
	};

	inline Elysium::Core::Template::Exceptions::ArgumentNullException::ArgumentNullException()
		: Elysium::Core::Template::Exceptions::ArgumentException(u8"ArgumentNullException")
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentNullException::ArgumentNullException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::ArgumentException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentNullException::ArgumentNullException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::ArgumentException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentNullException::~ArgumentNullException()
	{ }
}
#endif
