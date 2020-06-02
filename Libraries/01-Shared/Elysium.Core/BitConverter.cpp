#include "BitConverter.hpp"

#if defined(_WIN32) || defined(_WIN64) ||  defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(__CYGWIN__)
#define LITTLEENDIAN 1
#else
#error "unsupported os"
#endif


Elysium::Core::BitConverter::~BitConverter()
{ }

const bool Elysium::Core::BitConverter::GetIsLittleEndian()
{
#if defined LITTLEENDIAN
	return true;
#else
	return false;
#endif
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(int16_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8) });
#else
#error "unsupported os"
#endif
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(int32_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8), static_cast<byte>(Value >> 16), static_cast<byte>(Value >> 24) });
#else
#error "unsupported os"
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(int64_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8), static_cast<byte>(Value >> 16), static_cast<byte>(Value >> 24), static_cast<byte>(Value >> 32) , static_cast<byte>(Value >> 40) , static_cast<byte>(Value >> 48) , static_cast<byte>(Value >> 56) });
#else
#error "unsupported os"
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(uint16_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8) });
#else
#error "unsupported os"
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(uint32_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8), static_cast<byte>(Value >> 16), static_cast<byte>(Value >> 24) });
#else
#error "unsupported os"
#endif
}

const Elysium::Core::uint16_t Elysium::Core::BitConverter::ToUint16(byte * Value)
{
#if defined LITTLEENDIAN
	return uint16_t(Value[0] << 8 | Value[1]);
#else
#error "unsupported os"
#endif
}

Elysium::Core::BitConverter::BitConverter()
{ }
