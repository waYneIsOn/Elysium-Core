/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_MESSAGEAUTHENTICATIONCODEALGORITHM
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_MESSAGEAUTHENTICATIONCODEALGORITHM

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
	enum class MessageAuthenticationCodeAlgorithm
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class MessageAuthenticationCodeAlgorithm
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// None
		/// </summary>
		Null = 0,

		/// <summary>
		/// Message-Digest Algorithm 5
		/// </summary>
		MD5,

		/// <summary>
		/// Secure Hash Algorithm
		/// </summary>
		SHA,

		/// <summary>
		/// Secure Hash Algorith 2
		/// </summary>
		SHA256,
	};
}
#endif
#pragma once
