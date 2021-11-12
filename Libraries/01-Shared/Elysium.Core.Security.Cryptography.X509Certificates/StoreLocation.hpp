/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORELOCATION
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORELOCATION

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
	/// <summary>
	/// Specifies the location of the X.509 certificate store.
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class StoreLocation : Elysium::Core::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class StoreLocation
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// The X.509 certificate store used by the current user.
		/// </summary>
		CurrentUser = 0,

		/// <summary>
		/// The X.509 certificate store assigned to the local machine.
		/// </summary>
		LocalMachine = 1
	};
}
#endif
