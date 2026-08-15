/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_BULKENCRYPTIONALGORITHM
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_BULKENCRYPTIONALGORITHM

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
	enum class BulkEncryptionAlgorithm
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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
#pragma once
