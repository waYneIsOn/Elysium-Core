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
	enum class NotifyFilters : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class NotifyFilters
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		FileName = 1,

		/// <summary>
		/// 
		/// </summary>
		DirectoryName = 2,

		/// <summary>
		/// 
		/// </summary>
		Attributes = 4,

		/// <summary>
		/// 
		/// </summary>
		Size = 8,

		/// <summary>
		/// 
		/// </summary>
		LastWrite = 16,

		/// <summary>
		/// 
		/// </summary>
		LastAccess = 32,

		/// <summary>
		/// 
		/// </summary>
		CreationTime = 64,

		/// <summary>
		/// 
		/// </summary>
		Security = 256,
	};
}
#endif
