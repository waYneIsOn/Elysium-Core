/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_NOTIFYFILTERS
#define ELYSIUM_CORE_IO_NOTIFYFILTERS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::IO
{
	/// <summary>
	/// 
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class NotifyFilters : Elysium::Core::uint16_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class NotifyFilters
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		FileName = 0x01,

		/// <summary>
		/// 
		/// </summary>
		DirectoryName = 0x02,

		/// <summary>
		/// 
		/// </summary>
		Attributes = 0x04,

		/// <summary>
		/// 
		/// </summary>
		Size = 0x08,

		/// <summary>
		/// 
		/// </summary>
		LastWrite = 0x10,

		/// <summary>
		/// 
		/// </summary>
		LastAccess = 0x20,

		/// <summary>
		/// 
		/// </summary>
		CreationTime = 0x40,

		/// <summary>
		/// 
		/// </summary>
		Security = 0x100,
	};

	inline NotifyFilters operator|(const NotifyFilters Left, const NotifyFilters Right)
	{
		return static_cast<NotifyFilters>(static_cast<uint16_t>(Left) | static_cast<uint16_t>(Right));
	}

	inline NotifyFilters operator&(const NotifyFilters Left, const NotifyFilters Right)
	{
		return static_cast<NotifyFilters>(static_cast<uint16_t>(Left) & static_cast<uint16_t>(Right));
	}
}
#endif
