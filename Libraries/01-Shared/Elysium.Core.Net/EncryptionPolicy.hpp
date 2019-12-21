/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_NET_SECURITY_ENCRYPTIONPOLICY
#define ELYSIUM_CORE_NET_SECURITY_ENCRYPTIONPOLICY

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class EncryptionPolicy : uint32_t
#elif defined(__ANDROID__)
	enum class EncryptionPolicy
#else
#error "undefined os"
#endif
	{
		RequireEncryption = 0,
		AllowNoEncryption = 1,
		NoEncryption = 2
	};
}
#endif
