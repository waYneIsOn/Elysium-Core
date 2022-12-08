/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDCASTEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INVALIDCASTEXCEPTION

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
	/// The exception that is thrown for invalid casting or explicit conversion.
	/// </summary>
	class InvalidCastException : public SystemException
	{
	public:
		InvalidCastException();

		InvalidCastException(const char8_t* Message);

		InvalidCastException(Text::String<char8_t>&& Message);

		virtual ~InvalidCastException();
	};

	inline Elysium::Core::Template::Exceptions::InvalidCastException::InvalidCastException()
		: Elysium::Core::Template::Exceptions::SystemException(u8"InvalidCastException")
	{ }

	inline Elysium::Core::Template::Exceptions::InvalidCastException::InvalidCastException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::InvalidCastException::InvalidCastException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::SystemException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::InvalidCastException::~InvalidCastException()
	{ }
}
#endif
