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
	/// <summary>
	/// 
	/// </summary>
	class ELYSIUM_CORE_API Environment final
	{
	public:
		Environment() = delete;
		Environment(const Environment& Source) = delete;
		Environment(Environment&& Right) noexcept = delete;
		~Environment() = delete;

		Environment& operator=(const Environment& Source) = delete;
		Environment& operator=(Environment&& Right) noexcept = delete;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const bool Is64BitProcess();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::String MachineName();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::String& NewLine();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const OperatingSystem OSVersion();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::uint32_t ProcessorCount();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::String UserName();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		static const Elysium::Core::String SystemDirectory();
	private:
		static const Elysium::Core::String _NewLineCharacters;
	};
}
#endif
