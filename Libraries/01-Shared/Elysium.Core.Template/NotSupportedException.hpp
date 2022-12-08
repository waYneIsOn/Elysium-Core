/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NOTSUPPORTEDEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NOTSUPPORTEDEXCEPTION

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
	/// The exception that is thrown when an invoked method is not supported, or when there is an attempt to read, seek, or write to a stream that does 
	/// not support the invoked functionality.
	/// </summary>
	class NotSupportedException : public SystemException
	{
	public:
		NotSupportedException();

		NotSupportedException(const char8_t* Message);

		NotSupportedException(Text::String<char8_t>&& Message);

		virtual ~NotSupportedException();
	};

	inline Elysium::Core::Template::Exceptions::NotSupportedException::NotSupportedException()
		: Elysium::Core::Template::Exceptions::SystemException(u8"NotSupportedException")
	{ }

	inline Elysium::Core::Template::Exceptions::NotSupportedException::NotSupportedException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::NotSupportedException::NotSupportedException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::SystemException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::NotSupportedException::~NotSupportedException()
	{ }
}
#endif
