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

		Exception(const Exception& Source);

		Exception(Exception&& Right) noexcept = delete;

		virtual ~Exception();
	public:
		Exception& operator=(const Exception& Source) = delete;

		Exception& operator=(Exception&& Right) noexcept = delete;
	public:
		const Text::String<char8_t>& GetExceptionMessage() const noexcept;

		const Text::String<char8_t>& GetStackTrace() const noexcept;
	private:
		Text::String<char8_t> CaptureStackTrace();
	private:
		Text::String<char8_t> _Message;
		Text::String<char8_t> _StackTrace;
	};

	inline Elysium::Core::Template::Exceptions::Exception::Exception(const char8_t* Message)
		: _Message(Message), _StackTrace(CaptureStackTrace())
	{ }

	inline Exception::Exception(Text::String<char8_t> && Message)
		: _Message(Functional::Move(Message)), _StackTrace(CaptureStackTrace())
	{ }

	inline Exception::Exception(const Exception & Source)
		: _Message(Source._Message), _StackTrace(Source._StackTrace)
	{ }

	inline Elysium::Core::Template::Exceptions::Exception::~Exception()
	{ }

	inline const Text::String<char8_t>& Elysium::Core::Template::Exceptions::Exception::GetExceptionMessage() const noexcept
	{
		return _Message;
	}
	
	inline const Text::String<char8_t>& Elysium::Core::Template::Exceptions::Exception::GetStackTrace() const noexcept
	{
		return _StackTrace;
	}

	inline Text::String<char8_t> Exception::CaptureStackTrace()
	{	// ToDo: capture stacktrace as string like .net does
		return Text::String<char8_t>();
	}
}
#endif
