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

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const int16_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8) });
#else
	return Collections::Template::Array<byte>({ static_cast<byte>(Value >> 8), static_cast<byte>(Value & 0xFF) });
#endif
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const int32_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8), static_cast<byte>(Value >> 16), static_cast<byte>(Value >> 24) });
#else
	return Collections::Template::Array<byte>({ static_cast<byte>(Value >> 24),	static_cast<byte>(Value >> 16),	static_cast<byte>(Value >> 8), static_cast<byte>(Value & 0xFF) });
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const int64_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8), static_cast<byte>(Value >> 16), static_cast<byte>(Value >> 24), static_cast<byte>(Value >> 32), static_cast<byte>(Value >> 40), static_cast<byte>(Value >> 48), static_cast<byte>(Value >> 56) });
#else
	return Collections::Template::Array<byte>({	static_cast<byte>(Value >> 56),	static_cast<byte>(Value >> 48),	static_cast<byte>(Value >> 40),	static_cast<byte>(Value >> 32),	static_cast<byte>(Value >> 24),	static_cast<byte>(Value >> 16), static_cast<byte>(Value >> 8), static_cast<byte>(Value & 0xFF) });
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const uint16_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8) });
#else
	return Collections::Template::Array<byte>({ static_cast<byte>(Value >> 8), static_cast<byte>(Value & 0xFF) });
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const uint32_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8), static_cast<byte>(Value >> 16), static_cast<byte>(Value >> 24) });
#else
	return Collections::Template::Array<byte>({	static_cast<byte>(Value >> 24),	static_cast<byte>(Value >> 16),	static_cast<byte>(Value >> 8), static_cast<byte>(Value & 0xFF) });
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const uint64_t Value)
{
#if defined LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<byte>(Value & 0xFF), static_cast<byte>(Value >> 8), static_cast<byte>(Value >> 16), static_cast<byte>(Value >> 24), static_cast<byte>(Value >> 32), static_cast<byte>(Value >> 40), static_cast<byte>(Value >> 48), static_cast<byte>(Value >> 56) });
#else
	return Collections::Template::Array<byte>({	static_cast<byte>(Value >> 56),	static_cast<byte>(Value >> 48),	static_cast<byte>(Value >> 40),	static_cast<byte>(Value >> 32),	static_cast<byte>(Value >> 24),	static_cast<byte>(Value >> 16),	static_cast<byte>(Value >> 8), static_cast<byte>(Value & 0xFF) });
#endif
}

const Elysium::Core::int16_t Elysium::Core::BitConverter::ToInt16(const byte * Value)
{
#if defined LITTLEENDIAN
	return uint16_t(Value[0] << 8 | Value[1]);
#else
	return uint16_t(Value[0] | Value[1] << 8);
#endif
}
const Elysium::Core::int32_t Elysium::Core::BitConverter::ToInt24(const byte * Value)
{
#if defined LITTLEENDIAN
	return uint32_t(Value[0] << 16 | Value[1] << 8 | Value[2]);
#else
	return uint32_t(Value[0] | Value[1] << 8 | Value[2] << 16);
#endif
}
const Elysium::Core::int32_t Elysium::Core::BitConverter::ToInt32(const byte * Value)
{
#if defined LITTLEENDIAN
	return uint32_t(Value[0] << 24 | Value[1] << 16 | Value[2] << 8 | Value[3]);
#else
	return uint32_t(Value[0] | Value[1] << 8 | Value[2] << 16 | Value[3] << 24);
#endif
}
const Elysium::Core::int64_t Elysium::Core::BitConverter::ToInt64(const byte * Value)
{
#if defined LITTLEENDIAN
	return int64_t(Value[0] << 56 | Value[1] << 48 | Value[2] << 40 | Value[3] << 32 | Value[4] << 24 | Value[5] << 16 | Value[6] << 8 | Value[7]);
#else
	return int64_t(Value[0] | Value[1] << 8 | Value[2] << 16 | Value[3] << 24 | Value[4] << 32 | Value[5] << 40 | Value[6] << 48 | Value[7] << 56);
#endif
}
const Elysium::Core::uint16_t Elysium::Core::BitConverter::ToUint16(const byte * Value)
{
#if defined LITTLEENDIAN
	return uint16_t(Value[0] << 8 | Value[1]);
#else
	return uint16_t(Value[0] | Value[1] << 8);
#endif
}
const Elysium::Core::uint32_t Elysium::Core::BitConverter::ToUint24(const byte * Value)
{
#if defined LITTLEENDIAN
	return uint32_t(Value[0] << 16 | Value[1] << 8 | Value[2]);
#else
	return uint32_t(Value[0] | Value[1] << 8 | Value[2] << 16);
#endif
}
const Elysium::Core::uint32_t Elysium::Core::BitConverter::ToUint32(const byte * Value)
{
#if defined LITTLEENDIAN
	return uint32_t(Value[0] << 24 | Value[1] << 16 | Value[2] << 8 | Value[3]);
#else
	return uint32_t(Value[0] | Value[1] << 8 | Value[2] << 16 | Value[3] << 24);
#endif
}
const Elysium::Core::uint64_t Elysium::Core::BitConverter::ToUint64(const byte * Value)
{
#if defined LITTLEENDIAN
	return uint64_t(Value[0] << 56 | Value[1] << 48 | Value[2] << 40 | Value[3] << 32 | Value[4] << 24 | Value[5] << 16 | Value[6] << 8 | Value[7]);
#else
	return uint64_t(Value[0] | Value[1] << 8 |	Value[2] << 16 | Value[3] << 24 | Value[4] << 32 | Value[5] << 40 | Value[6] << 48 | Value[7] << 56);
#endif
}

Elysium::Core::BitConverter::BitConverter()
{ }
