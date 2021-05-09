#include "Char.hpp"

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTNULLEXCEPTION
#include "ArgumentNullException.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "ArgumentOutOfRangeException.hpp"
#endif

const Elysium::Core::String Elysium::Core::Char::ConvertFromUtf32(const Elysium::Core::uint32_t CodePoint)
{
	if (CodePoint < 0x80)			// 0 - 127
	{
		Elysium::Core::byte Bytes[1];
		Elysium::Core::byte* CodePointBytes = (Elysium::Core::byte*)&CodePoint;
#if defined LITTLEENDIAN
		Bytes[0] = CodePointBytes[0];
#else
		Bytes[0] = CodePointBytes[3];
#endif
		return Elysium::Core::String((const char8_t*)&Bytes[0], 1);
	}
	else if (CodePoint < 0x800)		// 128 - 2047
	{
		Elysium::Core::byte Bytes[2];
		Elysium::Core::byte* CodePointBytes = (Elysium::Core::byte*)&CodePoint;
#if defined LITTLEENDIAN
		Bytes[0] = 0xC0 | (CodePointBytes[1] << 2) | (CodePointBytes[0] >> 6);
		Bytes[1] = 0x80 | (CodePointBytes[0] & 0x3F);
#else
		throw 1;
#endif
		return Elysium::Core::String((const char8_t*)&Bytes[0], 2);
	}
	else if (CodePoint < 0x10000)	// 2048 - 65535
	{
		Elysium::Core::byte Bytes[3];
		Elysium::Core::byte* CodePointBytes = (Elysium::Core::byte*)&CodePoint;
#if defined LITTLEENDIAN
		Bytes[0] = 0xE0 | (CodePointBytes[1] >> 4);
		Bytes[1] = 0x80 | ((CodePointBytes[1] & 0x0F) << 2) | (CodePointBytes[0] >> 6);
		Bytes[2] = 0x80 | (CodePointBytes[0] & 0x3F);
#else
		throw 1;
#endif
		return Elysium::Core::String((const char8_t*)&Bytes[0], 3);
	}
	else if (CodePoint < 0x110000)	// 65536 - 1114111
	{
		Elysium::Core::byte Bytes[4];
		Elysium::Core::byte* CodePointBytes = (Elysium::Core::byte*)&CodePoint;
#if defined LITTLEENDIAN
		Bytes[0] = 0xF0 | ((CodePointBytes[2] & 0x1F) >> 2);
		Bytes[1] = 0x80 | ((CodePointBytes[2] & 0x03) << 4) | (CodePointBytes[1] >> 4);
		Bytes[2] = 0x80 | ((CodePointBytes[1] & 0x0F) << 2) | (CodePointBytes[0] >> 6);
		Bytes[3] = 0x80 | (CodePointBytes[0] & 0x3F);
#else
		throw 1;
#endif
		return Elysium::Core::String((const char8_t*)&Bytes[0], 4);
	}
	else
	{
		throw ArgumentOutOfRangeException(u8"CodePoint");
	}
}

const Elysium::Core::uint32_t Elysium::Core::Char::ConvertToUtf32(const char8_t* Input)
{
	if (Input == nullptr)
	{
		throw ArgumentNullException(u8"Input");
	}

	Elysium::Core::uint32_t CodePoint = 0;
	if (Input[0] >> 7 == 0x00)
	{	// 0-xxx xxxx											07 bit
#if defined LITTLEENDIAN
		CodePoint = Input[0];
#else
		throw 1;
#endif
	}
	else if (Input[0] >> 5 == 0x06)
	{	// 110-x xxyy	10-yy yyyy								11 bit
#if defined LITTLEENDIAN
		CodePoint = (((Input[0] >> 2) & 0x07) << 8) |
			(((Input[0] & 0x03) << 6) & (Input[1] & 0x3F));
#else
		throw 1;
#endif
	}
	else if (Input[0] >> 4 == 0x0E)
	{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
#if defined LITTLEENDIAN
		CodePoint = ((((Input[0] & 0x0F) << 4) | ((Input[1] >> 2) & 0x0F)) << 8) |
			(((Input[1] & 0x03) << 6) | Input[2] & 0x3F);
#else
		throw 1;
#endif
	}
	else if (Input[0] >> 3 == 0x1E)
	{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
#if defined LITTLEENDIAN
		CodePoint = ((((Input[0] & 0x07) << 2) | ((Input[1] >> 4) & 0x03)) << 16) |
			((((Input[1] & 0x0F) << 4) | ((Input[2] >> 2) & 0x0F)) << 8) |
			(((Input[2] & 0x03) << 6) | (Input[3] & 0x3F));
#else
		throw 1;
#endif
	}
	else
	{	// ToDo: InvalidDataException or something?
		throw 1;
	}

	return CodePoint;
}

const bool Elysium::Core::Char::IsControl(const char8_t Character, const char8_t FollowUpCharacter) noexcept
{	// In Unicode, "Control-characters" are U+0000—U+001F (C0 controls), U+007F (delete), and U+0080—U+009F (C1 controls)
	if ((Character >> 7) == 0x00)
	{
		Elysium::Core::uint8_t CodePoint = Character;
		if (CodePoint < 0x20)	// <= 0x1F
		{
			return true;
		}
		else if (CodePoint == 0x7F)
		{
			return true;
		}

		return false;
	}
	else if ((Character & 0xC0) == 0xC0)
	{
#if defined LITTLEENDIAN
		Elysium::Core::uint16_t CodePoint = (((Character >> 2) & 0x07) << 8) | (((Character & 0x03) << 6) | (FollowUpCharacter & 0x3F));
#else
		Elysium::Core::uint16_t CodePoint = (((FollowUpCharacter >> 2) & 0x07) << 8) | (((FollowUpCharacter & 0x03) << 6) | (Character & 0x3F));
#endif
		if (CodePoint < 0xA0)	// <= 0x9F
		{
			return true;
		}
	}

	return false;
}

const bool Elysium::Core::Char::IsDigit(const char8_t Character) noexcept
{	// ToDo: https://www.fileformat.info/info/unicode/category/Nd/list.htm
	return (Character > 29 && Character < 40) || (Character > 659 && Character < 670);
}

const bool Elysium::Core::Char::IsLeadByte(const char8_t Character) noexcept
{	// In UTF-8 a leading byte will always look like this: 0xxx xxxx, 110x xxxx, 1110 xxxx or 1111 0xxx
	if ((Character >> 7) == 0x00)
	{
		return true;
	}
	else if ((Character & 0xC0) == 0xC0)
	{
		return true;
	}
	else if ((Character & 0xE0) == 0xE0)
	{
		return true;
	}
	else if ((Character & 0xF0) == 0xF0)
	{
		return true;
	}

	return false;
}

const bool Elysium::Core::Char::IsTrailByte(const char8_t Character) noexcept
{	// In UTF-8 a trailing byte will always look like this: 10xx xxxx
	return (Character & 0x80) == 0x80;
}
