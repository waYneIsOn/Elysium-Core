/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_OPENFLAGS
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_OPENFLAGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::X509Certificates
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class OpenFlags : uint32_t
#elif defined(__ANDROID__)
	enum class OpenFlags
#else
#error "undefined os"
#endif
	{
		ReadOnly = 0,
		ReadWrite = 1,
		MaxAllowed = 2,
		OpenExistringOnly = 4,
		InlcudeArchived = 8
	};

	inline OpenFlags operator|(OpenFlags Left, OpenFlags Right)
	{
		return static_cast<OpenFlags>(static_cast<uint32_t>(Left) | static_cast<uint32_t>(Right));
	}
	inline OpenFlags operator&(OpenFlags Left, OpenFlags Right)
	{
		return static_cast<OpenFlags>(static_cast<uint32_t>(Left) & static_cast<uint32_t>(Right));
	}
}
#endif
