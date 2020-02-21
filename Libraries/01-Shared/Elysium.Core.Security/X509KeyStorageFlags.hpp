/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509KEYSTORAGEFLAGS
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509KEYSTORAGEFLAGS

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class X509KeyStorageFlags : uint32_t
#elif defined(__ANDROID__)
	enum class X509KeyStorageFlags
#else
#error "undefined os"
#endif
	{
		DefaultKeySet = 0,
		UserKeySet = 1,
		MachineKeySet = 2,
		Exportable = 4,
		UserProtected = 8,
		PersistKeySet = 16,
		EphemeralKeySet = 32
	};

	inline X509KeyStorageFlags operator|(X509KeyStorageFlags lhs, X509KeyStorageFlags rhs)
	{
		return static_cast<X509KeyStorageFlags>(static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
	}
	inline X509KeyStorageFlags operator&(X509KeyStorageFlags lhs, X509KeyStorageFlags rhs)
	{
		return static_cast<X509KeyStorageFlags>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
	}
}
#endif
