/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORENAME
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_STORENAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
	/// <summary>
	/// Specifies the name of the X.509 certificate store to open.
	/// </summary>
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class StoreName : uint8_t
#elif defined(__ANDROID__)
	enum class StoreName
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// The X.509 certificate store for other users.
		/// </summary>
		AddressBook = 1,

		/// <summary>
		/// The X.509 certificate store for third-party certificate authorities (CAs).
		/// </summary>
		AuthRoot = 2,

		/// <summary>
		/// The X.509 certificate store for intermediate certificate authorities (CAs).
		/// </summary>
		CertificateAuthority = 3,

		/// <summary>
		/// The X.509 certificate store for revoked certificates.
		/// </summary>
		Disallowed = 4,

		/// <summary>
		/// The X.509 certificate store for personal certificates.
		/// </summary>
		My = 5,

		/// <summary>
		/// The X.509 certificate store for trusted root certificate authorities (CAs).
		/// </summary>
		Root = 6,

		/// <summary>
		/// The X.509 certificate store for directly trusted people and resources.
		/// </summary>
		TrustedPeople = 7,

		/// <summary>
		/// The X.509 certificate store for directly trusted publishers.
		/// </summary>
		TrustedPublisher = 8
	};
}
#endif
