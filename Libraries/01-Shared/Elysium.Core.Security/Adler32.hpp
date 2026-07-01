/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32
#define ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_SECURITY_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32
#include "../Elysium.Core.Template/Security/Cryptography/Checksum/Adler32.hpp"
#endif

namespace Elysium::Core::Security::Cryptography::Checksum
{
	class ELYSIUM_CORE_SECURITY_API Elysium::Core::Template::Security::Cryptography::Checksum::Adler32;

	using Crc32 = Elysium::Core::Template::Security::Cryptography::Checksum::Adler32;
}
#endif
