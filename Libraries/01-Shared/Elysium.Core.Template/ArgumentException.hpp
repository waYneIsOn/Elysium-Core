/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_ARGUMENTEXCEPTION

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
	/// The exception that is thrown when one of the arguments provided to a method is not valid.
	/// </summary>
	class ArgumentException : public SystemException
	{
	public:
		ArgumentException();

		ArgumentException(const char8_t* Message);

		ArgumentException(Text::String<char8_t>&& Message);

		virtual ~ArgumentException();
	};

	inline Elysium::Core::Template::Exceptions::ArgumentException::ArgumentException()
		: Elysium::Core::Template::Exceptions::SystemException(u8"SystemException")
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentException::ArgumentException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentException::ArgumentException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::SystemException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::ArgumentException::~ArgumentException()
	{ }
}
#endif
