/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509KEYSTORAGEFLAGS
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_X509KEYSTORAGEFLAGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../System/OperatingSystem.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../System/Primitives.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::X509Certificates
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class X509KeyStorageFlags
		: Elysium::Core::Template::System::uint32_t
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

	inline X509KeyStorageFlags operator|(const X509KeyStorageFlags Left, const X509KeyStorageFlags Right)
	{
		return static_cast<X509KeyStorageFlags>(static_cast<Elysium::Core::Template::System::uint32_t>(Left) | static_cast<Elysium::Core::Template::System::uint32_t>(Right));
	}

	inline X509KeyStorageFlags operator&(const X509KeyStorageFlags Left, const X509KeyStorageFlags Right)
	{
		return static_cast<X509KeyStorageFlags>(static_cast<Elysium::Core::Template::System::uint32_t>(Left) & static_cast<Elysium::Core::Template::System::uint32_t>(Right));
	}
}
#endif
