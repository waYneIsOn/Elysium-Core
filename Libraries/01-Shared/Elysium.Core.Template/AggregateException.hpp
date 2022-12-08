/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_AGGREGATEEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_AGGREGATEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_EXCEPTION
#include "Exception.hpp"
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
	/// Represents one or more errors that occur during application execution.
	/// </summary>
	class AggregateException : public Exception
	{
	public:
		AggregateException();

		AggregateException(const char8_t* Message);

		AggregateException(Text::String<char8_t>&& Message);

		virtual ~AggregateException();
	};

	inline Elysium::Core::Template::Exceptions::AggregateException::AggregateException()
		: Elysium::Core::Template::Exceptions::Exception(u8"SystemException")
	{ }

	inline Elysium::Core::Template::Exceptions::AggregateException::AggregateException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::Exception(Message)
	{ }

	inline Elysium::Core::Template::Exceptions::AggregateException::AggregateException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::Exception(Functional::Move(Message))
	{ }

	inline Elysium::Core::Template::Exceptions::AggregateException::~AggregateException()
	{ }
}
#endif
