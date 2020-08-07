#include "UTF8Encoding.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte >Elysium::Core::Text::UTF8Encoding::_BOM = Collections::Template::Array<Elysium::Core::byte>({ 0xEF, 0xBB, 0xBF});

Elysium::Core::Text::UTF8Encoding::UTF8Encoding()
	: Elysium::Core::Text::UTF8Encoding(false, false)
{ }
Elysium::Core::Text::UTF8Encoding::UTF8Encoding(bool EncoderShouldEmitUTF8Identifier, bool ThrowOnInvalidBytes)
	: Elysium::Core::Text::Encoding(65001),	// WinNls.h -> CP_UTF8
	_EncoderShouldEmitUTF8Identifier(EncoderShouldEmitUTF8Identifier), _ThrowOnInvalidBytes(ThrowOnInvalidBytes)
{ }
Elysium::Core::Text::UTF8Encoding::~UTF8Encoding()
{ }

const bool Elysium::Core::Text::UTF8Encoding::GetIsSingleByte() const
{
	return false;
}
const Elysium::Core::String Elysium::Core::Text::UTF8Encoding::GetEncodingName() const
{
	return Elysium::Core::String(u8"Unicode (UTF-8)");
}

const Elysium::Core::uint32_t Elysium::Core::Text::UTF8Encoding::GetByteCount(const Elysium::Core::String & Input, const size_t CharIndex, const size_t CharCount) const
{
	Elysium::Core::uint32_t RequiredBytes = 0;
	unsigned char LeadByte;
	for (size_t i = 0; i < CharCount; ++i)
	{
		LeadByte = Input[i];
		if (LeadByte >> 7 == 0x00)
		{	// 0-xxx xxxx											07 bit
			RequiredBytes += 1;
		}
		else if (LeadByte >> 5 == 0x06)
		{	// 110-x xxxx	10-xx xyyy								11 bit
			if (_ThrowOnInvalidBytes)
			{
				ValidateTrailByte(Input[i + 1]);
			}
			RequiredBytes += 2;
			i++;
		}
		else if (LeadByte >> 4 == 0x0E)
		{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
			if (_ThrowOnInvalidBytes)
			{
				ValidateTrailByte(Input[i + 1]);
				ValidateTrailByte(Input[i + 2]);
			}
			RequiredBytes += 2;
			i += 2;
		}
		else if (LeadByte >> 3 == 0x1E)
		{	// 1111 0-xxx	10-xx xxxy	10-yy yyyy	10-yz zzz		21 bit
			if (_ThrowOnInvalidBytes)
			{
				ValidateTrailByte(Input[i + 1]);
				ValidateTrailByte(Input[i + 2]);
				ValidateTrailByte(Input[i + 3]);
			}
			RequiredBytes += 3;
			i += 3;
		}
		else if(_ThrowOnInvalidBytes)
		{	// we should have found a lead byte but haven't
			// ToDo: specific exception message
			throw Elysium::Core::ArgumentException(u8"leadbyte");
		}
	}

	return RequiredBytes;
}

Elysium::Core::Collections::Template::List<Elysium::Core::byte> Elysium::Core::Text::UTF8Encoding::GetBytes(const char Input) const
{
	// ToDo:
	throw 1;
}
Elysium::Core::Collections::Template::List<Elysium::Core::byte> Elysium::Core::Text::UTF8Encoding::GetBytes(const Elysium::Core::String & Input, const size_t CharIndex, const size_t CharCount) const
{
	const Elysium::Core::uint32_t RequiredSize = GetByteCount(Input, CharIndex, CharCount);
	Elysium::Core::Collections::Template::List<byte> Result = Elysium::Core::Collections::Template::List<byte>(RequiredSize);

	size_t ByteIndex = 0;
	unsigned char LeadByte;
	// no need to perform any checks here, since validation has already been done in GetByteCount(...) (if _ThrowOnInvalidBytes was enabled)
	for (size_t i = 0; i < CharCount; ++i)
	{
		LeadByte = Input[i];
		if (LeadByte >> 7 == 0x00)			// 0 - 127
		{	// 0xxxxxxx
			Result[ByteIndex++] = static_cast<byte>(LeadByte);
		}
		else if (LeadByte >> 5 == 0x06)		// 128 - 2047
		{	// 110xxxxx 10xxxxxx

			Result[ByteIndex++] = static_cast<byte>((LeadByte >> 2) & 0x07);
			Result[ByteIndex++] = static_cast<byte>(((LeadByte & 0x03) << 6) | (Input[i + 1] & 0x3F));
			++i;
		}
		else if (LeadByte >> 4 == 0x0E)		// 2048 - 65535
		{	// 1110xxxx 10xxxxxx 10xxxxxx
			Result[ByteIndex++] = static_cast<byte>(((LeadByte & 0x07) << 4) | ((Input[i + 1] & 0x3F) >> 2));
			Result[ByteIndex++] = static_cast<byte>(((Input[i + 1] & 0x3) << 6) | (Input[i + 2] & 0x3F));
			i += 2;
		}
		else if (LeadByte >> 3 == 0x1E)		// 65536 - 1114111
		{	// 11110xxx  10xxxxxx 10xxxxxx 10xxxxxx
			Result[ByteIndex++] = static_cast<byte>(((LeadByte & 0x07) << 2) | ((Input[i + 1] & 0x3F) >> 4));
			Result[ByteIndex++] = static_cast<byte>(((Input[i + 1] & 0x15) << 4) | ((Input[i + 2] & 0x3F) >> 2));
			Result[ByteIndex++] = static_cast<byte>(((Input[i + 2] & 0x3F) << 6) | (Input[i + 3] & 0x3F));
			i += 3;
		}
	}

	return Result;
}

const Elysium::Core::uint32_t Elysium::Core::Text::UTF8Encoding::GetCharCount(const Elysium::Core::byte * Bytes, const size_t ByteCount) const
{
	Elysium::Core::uint32_t RequiredCharacters = ByteCount;
	Elysium::Core::uint32_t IntegerRepresentation;
	for (size_t i = 0; i < ByteCount; ++i)
	{
		byte b1 = Bytes[i];

		IntegerRepresentation = Bytes[i];
		if (IntegerRepresentation < 0x80)
		{
			continue;
		}

		if (IntegerRepresentation < 0x800)
		{
			RequiredCharacters++;
		}
		else if (IntegerRepresentation < 0x10000)
		{
			RequiredCharacters += 2;
		}
		else if (IntegerRepresentation < 0x200000)
		{
			RequiredCharacters += 3;
		}
		else if (_ThrowOnInvalidBytes)
		{	// ToDo: specific exception message
			throw Elysium::Core::ArgumentException(u8"leadbyte");
		}
	}

	return RequiredCharacters;
}

Elysium::Core::String Elysium::Core::Text::UTF8Encoding::GetString(const Elysium::Core::byte * Bytes, const size_t ByteCount) const
{
	Elysium::Core::uint32_t RequiredCharacters = GetCharCount(Bytes, ByteCount);
	Elysium::Core::String Result = Elysium::Core::String(RequiredCharacters);

	Elysium::Core::uint32_t IntegerRepresentation;
	for (size_t i = 0; i < ByteCount; ++i)
	{
		IntegerRepresentation = Bytes[i];

		if (IntegerRepresentation < 0x80)				// 0xxx xxxx									->	0xxx xxxx
		{
			Result[i] = Bytes[i]; // no need for Bytes[i] & 0x7F since the first bit is 0 anyways
		}
		else if (IntegerRepresentation < 0x800)			// 110y yyyy	10xx xxxx						->	0000 0yyy	yyxx xxxx
		{
			Result[i] = Bytes[i];
			i++;
			/*
			Result[i] = ((Byte1 & 0x1F) << 6) | (Byte2 & 0x3F);
			Byte2 = Bytes[++i];
			Result[i] = ((Byte1 & 0x1F) << 6) | (Byte2 & 0x3F);
			*/
		}
		else if (IntegerRepresentation < 0x10000)	// 1110 zzzz	10yy yyyy	10xx xxxx				->	zzzz yyyy	yyxx xxxx
		{
			Result[i] = Bytes[i];
			i++;
			i++;
			/*
			Result[i] = ((Byte1 & 0x0F) << 12) | ((Byte2 & 0x3F) << 6) | (Byte3 & 0x3F);
			Byte2 = Bytes[++i];
			Result[i] = ((Byte1 & 0x0F) << 12) | ((Byte2 & 0x3F) << 6) | (Byte3 & 0x3F);
			Byte3 = Bytes[++i];
			Result[i] = ((Byte1 & 0x0F) << 12) | ((Byte2 & 0x3F) << 6) | (Byte3 & 0x3F);
			*/
		}
		else if (IntegerRepresentation < 0x200000)	// 1111 0aaa	10zz zzzz	10yy yyyyy	10xx xxxx	->	000a aazz	zzzz yyyy	yyxx xxxx
		{
			Result[i] = Bytes[i];
			i++;
			i++;
			i++;
			/*
			Result[i] = ((Byte1 & 0x07) << 18) | ((Byte2 & 0x3F) << 12) | ((Byte3 & 0x3F) << 6) | (Byte4 & 0x3F);
			Byte2 = Bytes[++i];
			Result[i] = ((Byte1 & 0x07) << 18) | ((Byte2 & 0x3F) << 12) | ((Byte3 & 0x3F) << 6) | (Byte4 & 0x3F);
			Byte3 = Bytes[++i];
			Result[i] = ((Byte1 & 0x07) << 18) | ((Byte2 & 0x3F) << 12) | ((Byte3 & 0x3F) << 6) | (Byte4 & 0x3F);
			Byte4 = Bytes[++i];
			Result[i] = ((Byte1 & 0x07) << 18) | ((Byte2 & 0x3F) << 12) | ((Byte3 & 0x3F) << 6) | (Byte4 & 0x3F);
			*/
		}
		else if (_ThrowOnInvalidBytes)
		{	// ToDo: specific exception message
			throw Elysium::Core::ArgumentException(u8"leadbyte");
		}
	}
	
	return Result;
}

void Elysium::Core::Text::UTF8Encoding::ValidateTrailByte(const Elysium::Core::byte TrailByte) const
{
	if ((TrailByte >> 6) & 0x03 != 0x02)
	{	// should have encountered a trial byte but didn't
		// ToDo: specific exception message
		throw Elysium::Core::ArgumentException(u8"trailbyte");
	}
}
