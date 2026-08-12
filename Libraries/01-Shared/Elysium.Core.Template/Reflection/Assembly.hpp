/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_REFLECTION_ASSEMBLY
#define ELYSIUM_CORE_TEMPLATE_REFLECTION_ASSEMBLY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../Container/Vector.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CHARACTERTRAITS
#include "../Text/CharacterTraits.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Text/String.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../Text/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_UNICODE_UTF16
#include "../Text/Unicode/Utf16.hpp"
#endif

#if defined ELYSIUM_CORE_OS_WINDOWS
#ifndef _APISETLIBLOADER_
#include <libloaderapi.h>
#endif


#else
#error "unsupported os"
#endif

namespace Elysium::Core::Template::Threading
{
	class ThreadPool;
}

namespace Elysium::Core::Template::Reflection
{
	class Assembly
	{
	private:
		friend class Elysium::Core::Template::Threading::ThreadPool;
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline constexpr Assembly(HMODULE AssemblyHandle)
			: _AssemblyHandle(AssemblyHandle), _FQPN(RetrieveFQPN(AssemblyHandle))
		{ }
#endif
	public:
		constexpr Assembly() = delete;

		constexpr Assembly(const Assembly& Source) = delete;

		constexpr Assembly(Assembly&& Right) noexcept = delete;

		constexpr ~Assembly() = default;
	public:
		constexpr Assembly& operator=(const Assembly& Source) = delete;

		constexpr Assembly& operator=(Assembly&& Right) noexcept = delete;
	public:
		inline const Elysium::Core::Template::Text::StringView<char8_t> GetFullName() const noexcept
		{
			return Elysium::Core::Template::Text::StringView<char8_t>(&_FQPN[0]);
		}

		inline const Elysium::Core::Template::Text::StringView<char8_t> GetName() const noexcept
		{
			const Elysium::Core::Template::System::size FPQNLength = _FQPN.GetLength();	// 48
			const Elysium::Core::Template::System::size LastIndexOfBackslash = Elysium::Core::Template::Text::CharacterTraits<char8_t>::LastIndexOf(&_FQPN[0], FPQNLength, '\\');	// 29
			if (static_cast<Elysium::Core::Template::System::size>(-1) == LastIndexOfBackslash)
			{
				return Elysium::Core::Template::Text::StringView<char8_t>(&_FQPN[0]);
			}

			return Elysium::Core::Template::Text::StringView<char8_t>(&_FQPN[LastIndexOfBackslash + sizeof(char8_t)], FPQNLength - LastIndexOfBackslash);
		}
	public:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static Assembly GetCallingAssembly()
		{
			HMODULE AssemblyHandle = nullptr;
			const BOOL QueryResult = GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<LPCWSTR>(&GetCallingAssembly), &AssemblyHandle);
			if (FALSE == QueryResult)
			{
				throw Elysium::Core::Template::Exceptions::SystemException();
			}

			return Assembly(AssemblyHandle);
		}
#endif
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		inline static Elysium::Core::Template::Text::String<char8_t> RetrieveFQPN(HMODULE AssemblyHandle)
		{
			Elysium::Core::Template::Container::Vector<wchar_t> Buffer(MAX_PATH);
			while (true)
			{
				Elysium::Core::Template::System::size CurrentCapacity = Buffer.GetCapacity();

				DWORD Length = GetModuleFileNameW(AssemblyHandle, &Buffer[0], CurrentCapacity);
				if (0 == Length)
				{
					throw Elysium::Core::Template::Exceptions::SystemException();
				}
				else if (Length < CurrentCapacity)
				{
					Buffer.Resize(Length);
					break;
				}
			}

			return Elysium::Core::Template::Text::Unicode::Utf16::FromSafeWideString<char8_t>(&Buffer[0], Buffer.GetLength());
		}
#endif
	private:
#if defined ELYSIUM_CORE_OS_WINDOWS
		HMODULE _AssemblyHandle;
#endif
		Elysium::Core::Template::Text::String<char8_t> _FQPN;
	};
}
#endif
