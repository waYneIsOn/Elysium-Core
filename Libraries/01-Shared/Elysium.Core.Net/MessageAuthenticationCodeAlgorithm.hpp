/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_MESSAGEAUTHENTICATIONCODEALGORITHM
#define ELYSIUM_CORE_NET_SECURITY_MESSAGEAUTHENTICATIONCODEALGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
	// Mac
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class MessageAuthenticationCodeAlgorithm : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
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



