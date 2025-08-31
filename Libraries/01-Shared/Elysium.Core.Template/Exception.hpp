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
	/// Represents errors that occure during application execution.
	/// </summary>
	class Exception
	{
	public:
		constexpr Exception(const char8_t* Message = nullptr);

		constexpr Exception(Text::String<char8_t>&& Message);

		constexpr Exception(const Exception& Source);

		constexpr Exception(Exception&& Right) noexcept;

		constexpr virtual ~Exception() = default;
	public:
		constexpr Exception& operator=(const Exception& Source);

		constexpr Exception& operator=(Exception&& Right) noexcept;
	public:
		const Text::String<char8_t>& GetExceptionMessage() const noexcept;

		const Text::String<char8_t>& GetStackTrace() const noexcept;
	private:
		constexpr Text::String<char8_t> CaptureStackTrace();
	private:
		Text::String<char8_t> _Message;
		Text::String<char8_t> _StackTrace;
	};

	inline constexpr Exception::Exception(const char8_t* Message)
		: _Message(Message), _StackTrace(CaptureStackTrace())
	{ }

	inline constexpr Exception::Exception(Text::String<char8_t> && Message)
		: _Message(Functional::Move(Message)), _StackTrace(CaptureStackTrace())
	{ }

	inline constexpr Exception::Exception(const Exception & Source)
		: _Message(Source._Message), _StackTrace(Source._StackTrace)
	{ }

	inline constexpr Exception::Exception(Exception&& Right) noexcept
		: _Message(), _StackTrace()
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}

	inline constexpr Exception& Elysium::Core::Template::Exceptions::Exception::operator=(const Exception& Source)
	{
		if (this != &Source)
		{
			_Message = Source._Message;
			_StackTrace = Source._StackTrace;
		}
		return *this;
	}

	inline constexpr Exception& Elysium::Core::Template::Exceptions::Exception::operator=(Exception&& Right) noexcept
	{
		if (this != &Right)
		{
			_Message = Elysium::Core::Template::Functional::Move(Right._Message);
			_StackTrace = Elysium::Core::Template::Functional::Move(Right._StackTrace);
		}
		return *this;
	}

	inline const Text::String<char8_t>& Elysium::Core::Template::Exceptions::Exception::GetExceptionMessage() const noexcept
	{
		return _Message;
	}
	
	inline const Text::String<char8_t>& Elysium::Core::Template::Exceptions::Exception::GetStackTrace() const noexcept
	{
		return _StackTrace;
	}

	inline constexpr Text::String<char8_t> Exception::CaptureStackTrace()
	{	// ToDo: capture stacktrace as string like .net does
		return Text::String<char8_t>();
	}
}
#endif
