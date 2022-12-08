/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NOTIMPLEMENTEDEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_NOTIMPLEMENTEDEXCEPTION

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
	/// The exception that is thrown when a requested method or operation is not implemented.
	/// </summary>
	class NotImplementedException : public SystemException
	{
	public:
		NotImplementedException();

		NotImplementedException(const char8_t* Message);

		NotImplementedException(Text::String<char8_t>&& Message);

		virtual ~NotImplementedException();
	};

	inline Elysium::Core::Template::Exceptions::NotImplementedException::NotImplementedException()
		: Elysium::Core::Template::Exceptions::SystemException(u8"NotImplementedException")
	{ }

	inline Elysium::Core::Template::Exceptions::NotImplementedException::NotImplementedException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::NotImplementedException::NotImplementedException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::SystemException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::NotImplementedException::~NotImplementedException()
	{ }
}
#endif
