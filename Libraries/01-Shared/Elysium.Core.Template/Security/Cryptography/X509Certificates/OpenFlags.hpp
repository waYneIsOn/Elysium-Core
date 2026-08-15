/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_OPENFLAGS
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_X509CERTIFICATES_OPENFLAGS

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
	enum class OpenFlags
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
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

	inline OpenFlags operator|(const OpenFlags Left, const OpenFlags Right)
	{
		return static_cast<OpenFlags>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) | static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}

	inline OpenFlags operator&(const OpenFlags Left, const OpenFlags Right)
	{
		return static_cast<OpenFlags>(static_cast<Elysium::Core::Template::System::uint8_t>(Left) & static_cast<Elysium::Core::Template::System::uint8_t>(Right));
	}
}
#endif
