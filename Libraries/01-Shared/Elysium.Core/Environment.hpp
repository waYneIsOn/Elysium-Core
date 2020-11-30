/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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
		static const Elysium::Core::String MachineName();
		static const Elysium::Core::String& NewLine();
		static const OperatingSystem OSVersion();
		static const Elysium::Core::uint32_t ProcessorCount();
		static const Elysium::Core::String UserName();
		static const Elysium::Core::String SystemDirectory();
		static const Elysium::Core::String _NewLineCharacters;
	};
}
#endif
