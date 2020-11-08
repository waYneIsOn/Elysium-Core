/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_ENVIRONMENT
#define ELYSIUM_CORE_ENVIRONMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_OPERATINGSYSTEM
#include "OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Environment final
	{
	public:
		Environment() = delete;
		Environment(const Environment& Source) = delete;
		Environment(Environment&& Right) noexcept = delete;
		~Environment() = delete;

		Environment& operator=(const Environment& Source) = delete;
		Environment& operator=(Environment&& Right) noexcept = delete;

		static constexpr const bool Is64BitProcess();
		static const String MachineName();
		static const String& NewLine();
		static const OperatingSystem OSVersion();
		static const Elysium::Core::uint32_t ProcessorCount();
		static const String UserName();
		static const String SystemDirectory();
		static const String _NewLineCharacters;
	};
}
#endif
