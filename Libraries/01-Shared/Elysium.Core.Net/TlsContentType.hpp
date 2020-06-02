/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_NET_SECURITY_TLSCONTENTTYPE
#define ELYSIUM_CORE_NET_SECURITY_TLSCONTENTTYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Net::Security
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class TlsContentType : uint8_t
#elif defined(__ANDROID__)
	enum class TlsContentType
#else
#error "undefined os"
#endif
	{
		ChanceCipherSpec = 0x14,	// 20
		Alert = 0x15,				// 21
		Handshake = 0x16,			// 22
		ApplicationData = 0x17		// 23
	};
}
#endif
