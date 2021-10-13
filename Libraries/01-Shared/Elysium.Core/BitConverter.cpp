#include "BitConverter.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

Elysium::Core::BitConverter::~BitConverter()
{ }

const bool Elysium::Core::BitConverter::GetIsLittleEndian()
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return true;
#else
	return false;
#endif
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const int16_t Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return Collections::Template::Array<Elysium::Core::byte>({ static_cast<Elysium::Core::byte>(Value & 0xFF), static_cast<Elysium::Core::byte>(Value >> 8) });
#else
	return Collections::Template::Array<Elysium::Core::byte>({ static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value & 0xFF) });
#endif
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const int32_t Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return Collections::Template::Array<Elysium::Core::byte>({ static_cast<Elysium::Core::byte>(Value & 0xFF), static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value >> 16), static_cast<Elysium::Core::byte>(Value >> 24) });
#else
	return Collections::Template::Array<Elysium::Core::byte>({ static_cast<Elysium::Core::byte>(Value >> 24),	static_cast<Elysium::Core::byte>(Value >> 16),	static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value & 0xFF) });
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const int64_t Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return Collections::Template::Array<Elysium::Core::byte>({ static_cast<Elysium::Core::byte>(Value & 0xFF), static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value >> 16), static_cast<Elysium::Core::byte>(Value >> 24), static_cast<Elysium::Core::byte>(Value >> 32), static_cast<Elysium::Core::byte>(Value >> 40), static_cast<Elysium::Core::byte>(Value >> 48), static_cast<Elysium::Core::byte>(Value >> 56) });
#else
	return Collections::Template::Array<Elysium::Core::byte>({	static_cast<Elysium::Core::byte>(Value >> 56),	static_cast<Elysium::Core::byte>(Value >> 48),	static_cast<Elysium::Core::byte>(Value >> 40),	static_cast<Elysium::Core::byte>(Value >> 32),	static_cast<Elysium::Core::byte>(Value >> 24),	static_cast<Elysium::Core::byte>(Value >> 16), static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value & 0xFF) });
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const uint16_t Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return Collections::Template::Array<Elysium::Core::byte>({ static_cast<Elysium::Core::byte>(Value & 0xFF), static_cast<Elysium::Core::byte>(Value >> 8) });
#else
	return Collections::Template::Array<Elysium::Core::byte>({ static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value & 0xFF) });
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const uint32_t Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<Elysium::Core::byte>(Value & 0xFF), static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value >> 16), static_cast<Elysium::Core::byte>(Value >> 24) });
#else
	return Collections::Template::Array<byte>({	static_cast<Elysium::Core::byte>(Value >> 24),	static_cast<Elysium::Core::byte>(Value >> 16),	static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value & 0xFF) });
#endif
}
const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::BitConverter::GetBytes(const uint64_t Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return Collections::Template::Array<byte>({ static_cast<Elysium::Core::byte>(Value & 0xFF), static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value >> 16), static_cast<Elysium::Core::byte>(Value >> 24), static_cast<Elysium::Core::byte>(Value >> 32), static_cast<Elysium::Core::byte>(Value >> 40), static_cast<Elysium::Core::byte>(Value >> 48), static_cast<Elysium::Core::byte>(Value >> 56) });
#else
	return Collections::Template::Array<byte>({	static_cast<Elysium::Core::byte>(Value >> 56),	static_cast<Elysium::Core::byte>(Value >> 48),	static_cast<Elysium::Core::byte>(Value >> 40),	static_cast<Elysium::Core::byte>(Value >> 32),	static_cast<Elysium::Core::byte>(Value >> 24),	static_cast<Elysium::Core::byte>(Value >> 16),	static_cast<Elysium::Core::byte>(Value >> 8), static_cast<Elysium::Core::byte>(Value & 0xFF) });
#endif
}

const Elysium::Core::int16_t Elysium::Core::BitConverter::ToInt16(const Elysium::Core::byte* Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return uint16_t(Value[0] << 8 | Value[1]);
#else
	return uint16_t(Value[0] | Value[1] << 8);
#endif
}
const Elysium::Core::int32_t Elysium::Core::BitConverter::ToInt24(const Elysium::Core::byte* Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return uint32_t(Value[0] << 16 | Value[1] << 8 | Value[2]);
#else
	return uint32_t(Value[0] | Value[1] << 8 | Value[2] << 16);
#endif
}
const Elysium::Core::int32_t Elysium::Core::BitConverter::ToInt32(const Elysium::Core::byte* Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return uint32_t(Value[0] << 24 | Value[1] << 16 | Value[2] << 8 | Value[3]);
#else
	return uint32_t(Value[0] | Value[1] << 8 | Value[2] << 16 | Value[3] << 24);
#endif
}
const Elysium::Core::int64_t Elysium::Core::BitConverter::ToInt64(const Elysium::Core::byte* Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	Elysium::Core::int32_t Low = uint32_t(Value[0] << 24 | Value[1] << 16 | Value[2] << 8 | Value[3]);
	Elysium::Core::int32_t High = uint32_t(Value[4] << 24 | Value[5] << 16 | Value[6] << 8 | Value[7]);

	return static_cast<Elysium::Core::int64_t>(High) << 32 | Low;
#else
	throw 1;
#endif
}
const Elysium::Core::uint16_t Elysium::Core::BitConverter::ToUInt16(const Elysium::Core::byte* Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return uint16_t(Value[0] << 8 | Value[1]);
#else
	return uint16_t(Value[0] | Value[1] << 8);
#endif
}
const Elysium::Core::uint32_t Elysium::Core::BitConverter::ToUInt24(const Elysium::Core::byte* Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return uint32_t(Value[0] << 16 | Value[1] << 8 | Value[2]);
#else
	return uint32_t(Value[0] | Value[1] << 8 | Value[2] << 16);
#endif
}
const Elysium::Core::uint32_t Elysium::Core::BitConverter::ToUInt32(const Elysium::Core::byte* Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	return uint32_t(Value[0] << 24 | Value[1] << 16 | Value[2] << 8 | Value[3]);
#else
	return uint32_t(Value[0] | Value[1] << 8 | Value[2] << 16 | Value[3] << 24);
#endif
}
const Elysium::Core::uint64_t Elysium::Core::BitConverter::ToUInt64(const Elysium::Core::byte* Value)
{
#if defined ELYSIUM_CORE_LITTLEENDIAN
	Elysium::Core::uint32_t Low = uint32_t(Value[0] << 24 | Value[1] << 16 | Value[2] << 8 | Value[3]);
	Elysium::Core::uint32_t High = uint32_t(Value[4] << 24 | Value[5] << 16 | Value[6] << 8 | Value[7]);

	return static_cast<Elysium::Core::uint64_t>(High) << 32 | Low;
#else
	throw 1;
#endif
}

Elysium::Core::BitConverter::BitConverter()
{ }
