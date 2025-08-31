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

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	#define _WINSOCKAPI_ // don't include winsock
	#include <Windows.h>
	#endif
#elif defined ELYSIUM_CORE_OS_LINUX

#elif defined ELYSIUM_CORE_OS_ANDROID

#else
	#error "unsupported os"
#endif

namespace Elysium::Core::Template::Exceptions
{
	/// <summary>
	/// Serves as the base class for system exceptions namespace.
	/// </summary>
	class SystemException 
		: public Exception
	{
	public:
		SystemException(const char8_t* Message = nullptr);

		SystemException(Text::String<char8_t>&& Message);

		constexpr SystemException(const System::uint32_t ErrorCode, const char8_t* Message = nullptr);

		constexpr SystemException(const SystemException& Source);

		constexpr SystemException(SystemException&& Right) noexcept;

		constexpr virtual ~SystemException() override = default;
	public:
		//constexpr SystemException& operator=(const SystemException& Source);

		//constexpr SystemException& operator=(SystemException&& Right) noexcept;
	public:
		constexpr const System::uint32_t GetErrorCode() const noexcept;
	private:
		Elysium::Core::Template::Text::String<char8_t> GetLastErrorMessage(DWORD ErrorCode);
	private:
		const System::uint32_t _ErrorCode;
	};

	inline Elysium::Core::Template::Exceptions::SystemException::SystemException(const char8_t* Message)
		: Elysium::Core::Template::Exceptions::Exception(Message),
 		_ErrorCode(GetLastError())
	{ }

	inline Elysium::Core::Template::Exceptions::SystemException::SystemException(Text::String<char8_t>&& Message)
		: Elysium::Core::Template::Exceptions::Exception(Functional::Move(Message)),
		_ErrorCode(GetLastError())
	{ }

	inline constexpr SystemException::SystemException(const System::uint32_t ErrorCode, const char8_t* Message)
		: Elysium::Core::Template::Exceptions::Exception(Message == nullptr ? 
			Elysium::Core::Template::Functional::Move(GetLastErrorMessage(ErrorCode)) : Message),
		_ErrorCode(ErrorCode)
	{ }

	inline constexpr SystemException::SystemException(const SystemException& Source)
		: _ErrorCode(Source._ErrorCode)
	{ }

	inline constexpr SystemException::SystemException(SystemException&& Right) noexcept
		: Elysium::Core::Template::Exceptions::Exception(Elysium::Core::Template::Functional::Move(Right)),
		_ErrorCode(Right._ErrorCode)
	{
	}

	inline constexpr const System::uint32_t Elysium::Core::Template::Exceptions::SystemException::GetErrorCode() const noexcept
	{
		return _ErrorCode;
	}

	inline Elysium::Core::Template::Text::String<char8_t> SystemException::GetLastErrorMessage(DWORD ErrorCode)
	{
		if (ErrorCode == 0)
		{
			return Elysium::Core::Template::Text::String<char8_t>();
		}

		LPWSTR MessageBuffer = nullptr;

		Elysium::Core::Template::System::size MessageLength = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, ErrorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPWSTR>(&MessageBuffer), 0, nullptr);

		Elysium::Core::Template::Text::String<char8_t> Result =
			Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(MessageBuffer, MessageLength);

		LocalFree(MessageBuffer);

		return Result;
	}
}
#endif
