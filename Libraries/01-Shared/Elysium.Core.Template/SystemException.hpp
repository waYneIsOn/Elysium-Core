/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION
#define ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_SYSTEMEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_EXCEPTIONS_EXCEPTION
#include "Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "String.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
	#elif defined(ELYSIUM_CORE_OS_ANDROID)
#else
	#error "unsupported os"
#endif

namespace Elysium::Core::Template::Exceptions
{
	/// <summary>
	/// Serves as the base class for system exceptions namespace.
	/// </summary>
	class SystemException : public Exception
	{
	public:
		SystemException();

		SystemException(const char8_t* Message);

		SystemException(Text::String<char8_t>&& Message);

		virtual ~SystemException();
	public:
		const System::uint32_t GetErrorCode() const noexcept;
	private:
		const System::uint32_t _ErrorCode;
	};

	inline Elysium::Core::Template::Exceptions::SystemException::SystemException()
		: Elysium::Core::Template::Exceptions::Exception(u8"SystemException"),
		_ErrorCode(GetLastError())
	{ }

	inline Elysium::Core::Template::Exceptions::SystemException::SystemException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::Exception(Message),
 		_ErrorCode(GetLastError())
	{ }

	inline Elysium::Core::Template::Exceptions::SystemException::SystemException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::Exception(Functional::Move(Message)),
		_ErrorCode(GetLastError())
	{ }

	inline Elysium::Core::Template::Exceptions::SystemException::~SystemException()
	{ }

	inline const System::uint32_t  Elysium::Core::Template::Exceptions::SystemException::GetErrorCode() const noexcept
	{
		return _ErrorCode;
	}
}
#endif
