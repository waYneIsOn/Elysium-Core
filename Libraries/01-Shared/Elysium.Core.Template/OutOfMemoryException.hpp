/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OUTOFMEMORYEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_OUTOFMEMORYEXCEPTION

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
	/// The exception that is thrown when there is not enough memory to continue the execution of a program.
	/// </summary>
	class OutOfMemoryException : public SystemException
	{
	public:
		OutOfMemoryException();

		OutOfMemoryException(const char8_t* Message);

		OutOfMemoryException(Text::String<char8_t>&& Message);

		virtual ~OutOfMemoryException();
	};

	inline Elysium::Core::Template::Exceptions::OutOfMemoryException::OutOfMemoryException()
		: Elysium::Core::Template::Exceptions::SystemException(u8"OutOfMemoryException")
	{ }

	inline Elysium::Core::Template::Exceptions::OutOfMemoryException::OutOfMemoryException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::OutOfMemoryException::OutOfMemoryException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::SystemException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::OutOfMemoryException::~OutOfMemoryException()
	{ }
}
#endif
