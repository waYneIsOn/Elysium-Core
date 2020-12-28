#include "Adler32.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "../Elysium.Core/ArgumentNullException.hpp"
#endif

constexpr const Elysium::Core::uint32_t Elysium::Core::Security::Cryptography::Checksum::Adler32::CalculateBytewise(const Elysium::Core::byte* Data, const size_t Length)
{
	if (Data == nullptr)
	{
		throw ArgumentNullException(u8"Data");
	}

	if (Length == 0)
	{
		return 0;
	}

	Elysium::Core::uint32_t A = 1;
	Elysium::Core::uint32_t B = 0;

	for (size_t i = 0; i < Length; ++i)
	{
		A = (A + Data[i]) % _Modulo;
		B = (B + A) % _Modulo;
	}

	return (B << 16) | A;
}
