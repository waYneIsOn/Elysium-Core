module;


#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_ADLER32
#include "Security/Cryptography/Checksum/Adler32.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_CHECKSUM_CRC32
#include "Security/Cryptography/Checksum/Crc32.hpp"
#endif

export module Elysium.Core.Template.Security.Cryptography.Checksum;

export
{
	using Elysium::Core::Template::Security::Cryptography::Checksum::Adler32;
	using Elysium::Core::Template::Security::Cryptography::Checksum::Crc32;
}
