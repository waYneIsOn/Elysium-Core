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
#include "../Functional/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Text/Unicode/Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
	#ifndef _WINDOWS_
	//#define _WINSOCKAPI_ // don't include winsock
	#define WIN32_LEAN_AND_MEAN
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
		inline constexpr SystemException(const char8_t* Message = nullptr)
			: Elysium::Core::Template::Exceptions::Exception(Message),
			_ErrorCode(GetLastError())
		{ }

		inline constexpr SystemException(const System::uint32_t ErrorCode, const char8_t* Message = nullptr)
			: Elysium::Core::Template::Exceptions::Exception(nullptr == Message ? &GetLastErrorMessage(ErrorCode)[0] : Message),
			_ErrorCode(ErrorCode)
		{ }

		inline constexpr SystemException(const SystemException& Source)
			: Elysium::Core::Template::Exceptions::Exception(Source),
			_ErrorCode(Source._ErrorCode)
		{ }

		inline constexpr SystemException(SystemException&& Right) noexcept
			: Elysium::Core::Template::Exceptions::Exception(Elysium::Core::Template::Functional::Move(Right)),
			_ErrorCode()
		{
			*this = Elysium::Core::Template::Functional::Move(Right);
		}

		virtual ~SystemException() override = default;
	public:
		inline constexpr SystemException& operator=(const SystemException& Source)
		{
			if (this != &Source)
			{
				//Elysium::Core::Template::Exceptions::Exception::operator=(Source);

				_ErrorCode = Source._ErrorCode;
			}
			return *this;
		}

		inline constexpr SystemException& operator=(SystemException&& Right) noexcept
		{
			if (this != &Right)
			{
				//Elysium::Core::Template::Exceptions::Exception::operator=(Right);

				_ErrorCode = Right._ErrorCode;

				Right._ErrorCode = 0;
			}
			return *this;
		}
	public:
		inline constexpr const System::uint32_t GetErrorCode() const noexcept
		{
			return _ErrorCode;
		}
	private:
		inline Elysium::Core::Template::Text::String<char8_t> GetLastErrorMessage(DWORD ErrorCode)
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
	private:
		System::uint32_t _ErrorCode;
	};
}
#endif
