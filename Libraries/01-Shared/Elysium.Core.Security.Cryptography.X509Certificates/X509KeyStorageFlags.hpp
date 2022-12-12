/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509KEYSTORAGEFLAGS
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509KEYSTORAGEFLAGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class X509KeyStorageFlags : uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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

		EphemeralKeySet = 32,

		All = DefaultKeySet | UserKeySet | MachineKeySet | Exportable | UserProtected | PersistKeySet | EphemeralKeySet,
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
