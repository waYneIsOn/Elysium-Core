/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_AUTHENTICATION_HASHALGORITHMTYPE
#define ELYSIUM_CORE_SECURITY_AUTHENTICATION_HASHALGORITHMTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::Core::Security::Authentication
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class HashAlgorithmType : Elysium::Core::uint16_t
#elif defined(__ANDROID__)
	enum class HashAlgorithmType
#else
#error "undefined os"
#endif
	{
		None = 0,

		Md5 = 32771,
		Sha1 = 32772,
		Sha256 = 32780,
		Sha384 = 32781,
		Sha512 = 32782,
	};
}
#endif
