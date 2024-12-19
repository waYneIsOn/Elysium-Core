/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INDEXOUTOFRANGEEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_INDEXOUTOFRANGEEXCEPTION

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
	/// The exception that is thrown when an attempt is made to access an element of an array or collection with an index that is outside its bounds.
	/// </summary>
	class IndexOutOfRangeException : public SystemException
	{
	public:
		IndexOutOfRangeException();

		IndexOutOfRangeException(const char8_t* Message);

		IndexOutOfRangeException(Text::String<char8_t>&& Message);

		IndexOutOfRangeException(const IndexOutOfRangeException& Source);

		virtual ~IndexOutOfRangeException();
	};

	inline Elysium::Core::Template::Exceptions::IndexOutOfRangeException::IndexOutOfRangeException()
		: Elysium::Core::Template::Exceptions::SystemException(u8"IndexOutOfRangeException")
	{ }

	inline Elysium::Core::Template::Exceptions::IndexOutOfRangeException::IndexOutOfRangeException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::SystemException(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::IndexOutOfRangeException::IndexOutOfRangeException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::SystemException(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::IndexOutOfRangeException::IndexOutOfRangeException(const IndexOutOfRangeException& Source)
	{ }

	inline Elysium::Core::Template::Exceptions::IndexOutOfRangeException::~IndexOutOfRangeException()
	{ }
}
#endif
