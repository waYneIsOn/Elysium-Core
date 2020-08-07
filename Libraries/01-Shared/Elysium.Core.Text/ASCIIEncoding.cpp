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
const Elysium::Core::String Elysium::Core::Text::ASCIIEncoding::GetEncodingName() const
{
	return Elysium::Core::String(u8"US-ASCII");
}

const Elysium::Core::uint32_t Elysium::Core::Text::ASCIIEncoding::GetByteCount(const Elysium::Core::String & Input, const size_t CharIndex, const size_t CharCount) const
{
	return static_cast<Elysium::Core::uint32_t>(CharCount);
}

Elysium::Core::Collections::Template::List<Elysium::Core::byte> Elysium::Core::Text::ASCIIEncoding::GetBytes(const char Input) const
{
	Elysium::Core::Collections::Template::List<Elysium::Core::byte> Result = Elysium::Core::Collections::Template::List<Elysium::Core::byte>(1);
	Elysium::Core::uint32_t IntegerRepresentation = Input;
	Result[0] = IntegerRepresentation < 0x80 ? static_cast<byte>(IntegerRepresentation) : 0x3F;

	return Result;
}
Elysium::Core::Collections::Template::List<Elysium::Core::byte> Elysium::Core::Text::ASCIIEncoding::GetBytes(const Elysium::Core::String & Input, const size_t CharIndex, const size_t CharCount) const
{
	Elysium::Core::Collections::Template::List<Elysium::Core::byte> Result = Elysium::Core::Collections::Template::List<Elysium::Core::byte>(CharCount);

	Elysium::Core::uint32_t IntegerRepresentation;
	for (size_t i = 0; i < CharCount; ++i)
	{
		IntegerRepresentation = Input[i];
		Result[i] = IntegerRepresentation < 0x80 ? static_cast<Elysium::Core::byte>(IntegerRepresentation) : 0x3F;
	}
	
	return Result;
}

const Elysium::Core::uint32_t Elysium::Core::Text::ASCIIEncoding::GetCharCount(const Elysium::Core::byte * Bytes, const size_t ByteCount) const
{
	return static_cast<Elysium::Core::uint32_t>(ByteCount);
}

Elysium::Core::String Elysium::Core::Text::ASCIIEncoding::GetString(const Elysium::Core::byte * Bytes, const size_t ByteCount) const
{
	String Result = String(ByteCount);
	for (size_t i = 0; i < ByteCount; ++i)
	{
		Result[i] = Bytes[i];
	}

	return Result;
}
