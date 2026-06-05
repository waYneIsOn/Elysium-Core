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
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

namespace Elysium::Core::Template::Exceptions
{
	/// <summary>
	/// Represents errors that occure during application execution.
	/// </summary>
	class Exception
	{
	public:
		inline constexpr Exception(const char8_t* Message = nullptr)
			: _Message(Message), _StackTrace(CaptureStackTrace())
		{ }

		inline constexpr Exception(const Exception& Source)
			: _Message(Source._Message), _StackTrace(Source._StackTrace)
		{ }

		inline constexpr Exception(Exception&& Right) noexcept
			: _Message(), _StackTrace()
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		virtual ~Exception() = default;
	public:
		inline constexpr Exception& operator=(const Exception& Source)
		{
			if (this != &Source)
			{
				_Message = Source._Message;
				_StackTrace = Source._StackTrace;
			}
			return *this;
		}

		inline constexpr Exception& operator=(Exception&& Right) noexcept
		{
			if (this != &Right)
			{
				_Message = Elysium::Core::Template::Functional::Move(Right._Message);
				_StackTrace = Elysium::Core::Template::Functional::Move(Right._StackTrace);
			}
			return *this;
		}
	public:
		inline const Elysium::Core::Template::Text::String<char8_t>& GetExceptionMessage() const noexcept
		{
			return _Message;
		}

		inline const Elysium::Core::Template::Text::String<char8_t>& GetStackTrace() const noexcept
		{
			return _StackTrace;
		}
	private:
		inline constexpr Elysium::Core::Template::Text::String<char8_t> CaptureStackTrace()
		{	// @ToDo: capture stacktrace as string like .net does
			return Elysium::Core::Template::Text::String<char8_t>();
		}
	private:
		Elysium::Core::Template::Text::String<char8_t> _Message;
		Elysium::Core::Template::Text::String<char8_t> _StackTrace;
	};
}
#endif
