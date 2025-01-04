#include "ASCIIEncoding.hpp"

Elysium::Core::Text::ASCIIEncoding::ASCIIEncoding()
	: Elysium::Core::Text::Encoding(20127)
{ }

Elysium::Core::Text::ASCIIEncoding::~ASCIIEncoding()
{ }

const bool Elysium::Core::Text::ASCIIEncoding::GetIsSingleByte() const
{
	return true;
}

const Elysium::Core::Utf8String& Elysium::Core::Text::ASCIIEncoding::GetEncodingName() const
{
	static Elysium::Core::Utf8String EncodingName = u8"US-ASCII";
	return EncodingName;
}

const Elysium::Core::Container::VectorOfByte& Elysium::Core::Text::ASCIIEncoding::GetPreamble() const
{
	static Elysium::Core::Container::VectorOfByte Preamble = Elysium::Core::Container::VectorOfByte(0);
	return Preamble;
}

const Elysium::Core::uint32_t Elysium::Core::Text::ASCIIEncoding::GetByteCount(const char8_t * Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	return static_cast<Elysium::Core::uint32_t>(CharCount + AdditionalCount);
}

Elysium::Core::Container::VectorOfByte Elysium::Core::Text::ASCIIEncoding::GetBytes(const char8_t * Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	Elysium::Core::Container::VectorOfByte Result =
		Elysium::Core::Container::VectorOfByte(GetByteCount(Input, CharCount, AdditionalCount));

	Elysium::Core::uint32_t IntegerRepresentation;
	for (Elysium::Core::size i = 0; i < CharCount; ++i)
	{
		IntegerRepresentation = Input[i];
		Result[i] = IntegerRepresentation < 0x80 ? static_cast<Elysium::Core::byte>(IntegerRepresentation) : 0x3F;
	}
	
	return Result;
}

const Elysium::Core::uint32_t Elysium::Core::Text::ASCIIEncoding::GetCharCount(const Elysium::Core::byte * Bytes, const Elysium::Core::size ByteCount) const
{
	return static_cast<Elysium::Core::uint32_t>(ByteCount);
}

Elysium::Core::Utf8String Elysium::Core::Text::ASCIIEncoding::GetString(const Elysium::Core::byte * Bytes, const Elysium::Core::size ByteCount) const
{
	Utf8String Result = Utf8String(ByteCount);
	for (Elysium::Core::size i = 0; i < ByteCount; ++i)
	{
		Result[i] = Bytes[i];
	}

	return Result;
}
