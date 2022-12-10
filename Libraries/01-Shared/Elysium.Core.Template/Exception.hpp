/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_EXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_EXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_DIAGNOSTICS_STACKTRACE
#include "StackTrace.hpp"
#endif

namespace Elysium::Core::Template::Exceptions
{
	/// <summary>
	/// Represents errors that occur during application execution.
	/// </summary>
	class Exception
	{
	public:
		Exception(const char8_t* Message = nullptr);

		Exception(Text::String<char8_t>&& Message);

		Exception(const Exception& Source) = delete;

		Exception(Exception&& Right) noexcept = delete;

		virtual ~Exception();
	public:
		Exception& operator=(const Exception& Source) = delete;

		Exception& operator=(Exception&& Right) noexcept = delete;
	public:
		const Text::String<char8_t>& GetExceptionMessage() const noexcept;

		const Diagnostics::StackTrace& GetStackTrace() const noexcept;
	private:
		Text::String<char8_t> _Message;
		Diagnostics::StackTrace _StackTrace;
	};

	inline Elysium::Core::Template::Exceptions::Exception::Exception(const char8_t* Message)
		: _Message(Message), _StackTrace(Diagnostics::StackTrace())
	{ }

	inline Exception::Exception(Text::String<char8_t> && Message)
		: _Message(Functional::Move(Message)), _StackTrace(Diagnostics::StackTrace())
	{ }

	inline Elysium::Core::Template::Exceptions::Exception::~Exception()
	{ }

	inline const Text::String<char8_t>& Elysium::Core::Template::Exceptions::Exception::GetExceptionMessage() const noexcept
	{
		return _Message;
	}
	
	inline const Diagnostics::StackTrace& Elysium::Core::Template::Exceptions::Exception::GetStackTrace() const noexcept
	{
		return _StackTrace;
	}
}
#endif
