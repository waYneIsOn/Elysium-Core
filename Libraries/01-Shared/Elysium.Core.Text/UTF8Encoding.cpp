#include "UTF8Encoding.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

Elysium::Core::Text::UTF8Encoding::UTF8Encoding()
	: Elysium::Core::Text::UTF8Encoding(false, false)
{ }

Elysium::Core::Text::UTF8Encoding::UTF8Encoding(const bool EncoderShouldEmitIdentifier, const bool ThrowOnInvalidBytes)
	: Elysium::Core::Text::Encoding(65001),	// WinNls.h -> CP_UTF8
	_EncoderShouldEmitIdentifier(EncoderShouldEmitIdentifier), _ThrowOnInvalidBytes(ThrowOnInvalidBytes)
{ }

Elysium::Core::Text::UTF8Encoding::~UTF8Encoding()
{ }

const bool Elysium::Core::Text::UTF8Encoding::GetIsSingleByte() const
{
	return false;
}

const Elysium::Core::Utf8String& Elysium::Core::Text::UTF8Encoding::GetEncodingName() const
{
	static const Elysium::Core::Utf8String EncodingName = u8"Unicode (UTF-8)";
	return EncodingName;
}

const Elysium::Core::Container::VectorOfByte& Elysium::Core::Text::UTF8Encoding::GetPreamble() const
{
	if (_EncoderShouldEmitIdentifier)
	{
		static const Elysium::Core::Container::VectorOfByte Preamble = { 0xEF, 0xBB, 0xBF };
		return Preamble;
	}
	else
	{
		static const Elysium::Core::Container::VectorOfByte Preamble = Elysium::Core::Container::VectorOfByte(0);
		return Preamble;
	}
}

const Elysium::Core::uint32_t Elysium::Core::Text::UTF8Encoding::GetByteCount(const char8_t * Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	return static_cast<Elysium::Core::uint32_t>(CharCount + AdditionalCount);

	/*
	// UTF-16 BE
	Elysium::Core::uint32_t RequiredBytes = 0;
	byte LeadByte;
	for (Elysium::Core::size i = 0; i < CharCount; ++i)
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
	*/
}

Elysium::Core::Container::VectorOfByte Elysium::Core::Text::UTF8Encoding::GetBytes(const char8_t * Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	const Elysium::Core::uint32_t RequiredSize = GetByteCount(Input, CharCount);
	Elysium::Core::Container::VectorOfByte Result = Elysium::Core::Container::VectorOfByte(RequiredSize);
	for (Elysium::Core::size i = 0; i < CharCount; ++i)
	{
		Result[i] = static_cast<Elysium::Core::byte>(Input[i]);
	}
	return Result;


	/*
	// UTF-16 BE
	Elysium::Core::size ByteIndex = 0;
	unsigned char LeadByte;
	// no need to perform any checks here, since validation has already been done in GetByteCount(...) (if _ThrowOnInvalidBytes was enabled)
	for (Elysium::Core::size i = 0; i < CharCount; ++i)
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
	*/
}

const Elysium::Core::uint32_t Elysium::Core::Text::UTF8Encoding::GetCharCount(const Elysium::Core::byte * Bytes, const Elysium::Core::size ByteCount) const
{
	return static_cast<Elysium::Core::uint32_t>(ByteCount);
	/*
	// UTF-16 BE
	Elysium::Core::uint32_t RequiredCharacters = ByteCount;
	Elysium::Core::byte FirstByte;
	for (Elysium::Core::size i = 0; i < ByteCount; ++i)
	{
		FirstByte = Bytes[i];
		if (FirstByte > 0x7F)
		{	// multiple bytes
			if (FirstByte & 0x20 != 0x00)
			{
				if (FirstByte & 0x10 != 0x00)
				{	// four bytes
					RequiredCharacters += 3;
					i += 3;
				}
				else
				{	// three bytes
					RequiredCharacters += 2;
					i += 2;
				}
			}
			else
			{	// two bytes
				RequiredCharacters++;
				i++;
			}
		}
		else
		{
			int x = 45;
		}
	}

	return RequiredCharacters;
	*/
}

Elysium::Core::Utf8String Elysium::Core::Text::UTF8Encoding::GetString(const Elysium::Core::byte * Bytes, const Elysium::Core::size ByteCount) const
{
	Elysium::Core::uint32_t RequiredCharacters = GetCharCount(Bytes, ByteCount);
	Elysium::Core::Utf8String Result = Elysium::Core::Utf8String(RequiredCharacters);
	for (Elysium::Core::size i = 0; i < ByteCount; ++i)
	{
		Result[i] = static_cast<char>(Bytes[i]);
	}
	return Result;
	/*
	Elysium::Core::uint32_t IntegerRepresentation;
	for (Elysium::Core::size i = 0; i < ByteCount; ++i)
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
			*-/
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
			*-/
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
			*-/
		}
		else if (_ThrowOnInvalidBytes)
		{	// ToDo: specific exception message
			throw Elysium::Core::ArgumentException(u8"leadbyte");
		}
	}
	
	return Result;
	*/
}
