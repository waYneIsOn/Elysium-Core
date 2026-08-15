/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSCONTENTTYPE
#define ELYSIUM_CORE_TEMPLATE_NET_SECURITY_TLSCONTENTTYPE

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
	/// <summary>
	/// ...
	/// 
	/// https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-5
	/// </summary>
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class TlsContentType
		: Elysium::Core::Template::System::uint8_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class TlsContentType
#else
#error "undefined os"
#endif
	{
		ChanceCipherSpec = 0x14,	// 20

		Alert = 0x15,				// 21

		Handshake = 0x16,			// 22

		ApplicationData = 0x17,		// 23

		Heartbeat = 0x18,			// 24
	};
}
#endif
#pragma once
