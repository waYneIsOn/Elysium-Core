/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTOUTOFRANGEEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTOUTOFRANGEEXCEPTION

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
	/// The exception that is thrown when the value of an argument is outside the allowable range of values as defined by the invoked method.
	/// </summary>
	class ArgumentOutOfRangeException : public ArgumentException
	{
	public:
		ArgumentOutOfRangeException();

		ArgumentOutOfRangeException(const char8_t* Message);

		ArgumentOutOfRangeException(Text::String<char8_t>&& Message);

		virtual ~ArgumentOutOfRangeException();
	};

	inline Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException::ArgumentOutOfRangeException()
		: Elysium::Core::Template::Exceptions::ArgumentException(u8"ArgumentOutOfRangeException")
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException::ArgumentOutOfRangeException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::ArgumentException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException::ArgumentOutOfRangeException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::ArgumentException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentOutOfRangeException::~ArgumentOutOfRangeException()
	{ }
}
#endif
