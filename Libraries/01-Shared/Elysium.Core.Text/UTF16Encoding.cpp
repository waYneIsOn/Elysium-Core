#include "UTF16Encoding.hpp"

/*
void Elysium::Core::Text::UTF16Encoding::ValidateTrailByte(const Elysium::Core::byte TrailByte) const
{
	if ((TrailByte >> 6) & 0x03 != 0x02)
	{	// should have encountered a trial byte but didn't
		// ToDo: specific exception message
		throw Elysium::Core::ArgumentException(u8"trailbyte");
	}
}
*/

Elysium::Core::Text::UTF16Encoding::UTF16Encoding()
	: Elysium::Core::Text::UTF16Encoding(false, false, false)
{ }
Elysium::Core::Text::UTF16Encoding::UTF16Encoding(bool BigEndian, bool EncoderShouldEmitUTF8Identifier, bool ThrowOnInvalidBytes)
	: Elysium::Core::Text::Encoding(BigEndian ? 1200 : 1201),
	_BigEndian(BigEndian), _EncoderShouldEmitUTF8Identifier(EncoderShouldEmitUTF8Identifier), _ThrowOnInvalidBytes(ThrowOnInvalidBytes)
{ }
Elysium::Core::Text::UTF16Encoding::~UTF16Encoding()
{ }

const bool Elysium::Core::Text::UTF16Encoding::GetIsSingleByte() const
{
	return false;
}

const Elysium::Core::String Elysium::Core::Text::UTF16Encoding::GetEncodingName() const
{
	if (_BigEndian)
	{
		static Elysium::Core::String EncodingName = Elysium::Core::String(u8"Unicode (UTF-16 Big-Endian)");
		return EncodingName;
	}
	else
	{
		static Elysium::Core::String EncodingName = Elysium::Core::String(u8"Unicode (UTF-16 Little-Endian)");
		return EncodingName;
	}
}

const Elysium::Core::uint32_t Elysium::Core::Text::UTF16Encoding::GetByteCount(const Elysium::Core::String & Input, const size_t CharIndex, const size_t CharCount) const
{
	return Elysium::Core::uint32_t();
}

Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Text::UTF16Encoding::GetBytes(const Elysium::Core::String & Input, const size_t CharIndex, const size_t CharCount) const
{
	return Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(0);
}

const Elysium::Core::uint32_t Elysium::Core::Text::UTF16Encoding::GetCharCount(const Elysium::Core::byte * Bytes, const size_t ByteCount) const
{
	return Elysium::Core::uint32_t();
}

Elysium::Core::String Elysium::Core::Text::UTF16Encoding::GetString(const Elysium::Core::byte * Bytes, const size_t ByteCount) const
{
	return Elysium::Core::String();
}
