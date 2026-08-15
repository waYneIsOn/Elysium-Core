/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_KEYEXCHANGEALGORITHM
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_KEYEXCHANGEALGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Net::Security
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class KeyExchangeAlgorithm
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class KeyExchangeAlgorithm
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// None
		/// </summary>
		Null = 0,

		/// <summary>
		/// 
		/// </summary>
		RSA,

		/// <summary>
		/// 
		/// </summary>
		DH_DSS,

		/// <summary>
		/// 
		/// </summary>
		DH_RSA,

		/// <summary>
		/// 
		/// </summary>
		DHE_DSS,

		/// <summary>
		/// 
		/// </summary>
		DHE_RSA,

		/// <summary>
		/// 
		/// </summary>
		DH_anon,

		/// <summary>
		/// 
		/// </summary>
		ECHDE,
	};
}
#endif
#pragma once
