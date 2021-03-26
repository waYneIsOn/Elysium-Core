/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_BULKENCRYPTIONALGORITHM
#define ELYSIUM_CORE_NET_SECURITY_BULKENCRYPTIONALGORITHM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
	// Cipher
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class BulkEncryptionAlgorithm : Elysium::Core::uint8_t
#elif defined(__ANDROID__)
	enum class BulkEncryptionAlgorithm
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// None
		/// </summary>
		Null = 0,

		/// <summary>
		/// Rivest Cipher 4
		/// </summary>
		RC4_128,

		/// <summary>
		/// Triple Data Encryption Standard
		/// </summary>
		TDES_EDE_CBC,

		/// <summary>
		/// Advanced Encryption Standard
		/// </summary>
		AES_128_CBC,

		/// <summary>
		/// Advanced Encryption Standard
		/// </summary>
		AES_256_CBC,
	};
}
#endif



