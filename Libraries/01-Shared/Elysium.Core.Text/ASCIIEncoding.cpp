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
const Elysium::Core::String& Elysium::Core::Text::ASCIIEncoding::GetEncodingName() const
{
	static Elysium::Core::String EncodingName = Elysium::Core::String(u8"US-ASCII");
	return EncodingName;
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Elysium::Core::Text::ASCIIEncoding::GetPreamble() const
{
	static Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Preamble =
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(0);
	return Preamble;
}

const Elysium::Core::uint32_t Elysium::Core::Text::ASCIIEncoding::GetByteCount(const char8_t * Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	return static_cast<Elysium::Core::uint32_t>(CharCount + AdditionalCount);
}

Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Text::ASCIIEncoding::GetBytes(const char8_t * Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Result = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(GetByteCount(Input, CharCount, AdditionalCount), AdditionalCount > 0 ? true : false);

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

Elysium::Core::String Elysium::Core::Text::ASCIIEncoding::GetString(const Elysium::Core::byte * Bytes, const Elysium::Core::size ByteCount) const
{
	String Result = String(ByteCount);
	for (Elysium::Core::size i = 0; i < ByteCount; ++i)
	{
		Result[i] = Bytes[i];
	}

	return Result;
}
