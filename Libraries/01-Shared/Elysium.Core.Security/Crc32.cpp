#include "Crc32.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "../Elysium.Core/ArgumentNullException.hpp"
#endif

const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::Checksum::Crc32::CalculateBytewise(const Elysium::Core::byte* Data, const Elysium::Core::size Length)
{
	if (Data == nullptr)
	{
		throw ArgumentNullException(u8"Data");
	}

	if (Length == 0)
	{
		return 0;
	}

	// Todd K. Moon, "Error Correction Coding. Mathematical Methods and Algorithms", Wiley, 2005, ISBN 0-471-64800-0
	Elysium::Core::uint32_t Checksum = 0xFFFFFFFF;
	Elysium::Core::uint32_t LookupTableIndex;
	for (Elysium::Core::size i = 0; i < Length; ++i)
	{
		LookupTableIndex = (Data[i] ^ Checksum) & 0xFF;
		Checksum = (Checksum >> 8) ^ _LookupTable[LookupTableIndex];
	}

	return ~Checksum;
}
