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
		~Environment();

		static constexpr const bool Is64BitProcess();
		static const String MachineName();
		static const String& NewLine();
		static const OperatingSystem OSVersion();
		static const uint32_t ProcessorCount();
		static const String UserName();
		static const String SystemDirectory();
	private:
		Environment();

		static const String _NewLineCharacters;
	};
}
#endif
