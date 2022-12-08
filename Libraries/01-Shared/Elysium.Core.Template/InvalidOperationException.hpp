/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDOPERATIONEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDOPERATIONEXCEPTION

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
	/// The exception that is thrown when a method call is invalid for the object's current state.
	/// </summary>
	class InvalidOperationException : public SystemException
	{
	public:
		InvalidOperationException();

		InvalidOperationException(const char8_t* Message);

		InvalidOperationException(Text::String<char8_t>&& Message);

		virtual ~InvalidOperationException();
	};

	inline Elysium::Core::Template::Exceptions::InvalidOperationException::InvalidOperationException()
		: Elysium::Core::Template::Exceptions::SystemException(u8"InvalidOperationException")
	{ }

	inline Elysium::Core::Template::Exceptions::InvalidOperationException::InvalidOperationException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::InvalidOperationException::InvalidOperationException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::SystemException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::InvalidOperationException::~InvalidOperationException()
	{ }
}
#endif
