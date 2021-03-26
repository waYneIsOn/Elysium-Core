/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_KEYEXCHANGEALGORITHM
#define ELYSIUM_CORE_NET_SECURITY_KEYEXCHANGEALGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
	// Key exchange
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class KeyExchangeAlgorithm : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
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



