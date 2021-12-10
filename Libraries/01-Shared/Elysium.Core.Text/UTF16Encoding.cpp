#include "UTF16Encoding.hpp"

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

Elysium::Core::Text::UTF16Encoding::UTF16Encoding()
	: Elysium::Core::Text::UTF16Encoding(false, false, false)
{ }
Elysium::Core::Text::UTF16Encoding::UTF16Encoding(const bool BigEndian, const bool EncoderShouldEmitIdentifier, const bool ThrowOnInvalidBytes)
	: Elysium::Core::Text::Encoding(BigEndian ? 1201 : 1200),
	_BigEndian(BigEndian), _EncoderShouldEmitIdentifier(EncoderShouldEmitIdentifier), _ThrowOnInvalidBytes(ThrowOnInvalidBytes)
{ }
Elysium::Core::Text::UTF16Encoding::~UTF16Encoding()
{ }

const bool Elysium::Core::Text::UTF16Encoding::GetIsSingleByte() const
{
	return false;
}

const Elysium::Core::String& Elysium::Core::Text::UTF16Encoding::GetEncodingName() const
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

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Elysium::Core::Text::UTF16Encoding::GetPreamble() const
{
	if (_EncoderShouldEmitIdentifier)
	{
		if (_BigEndian)
		{
			static Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Preamble = 
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte>({ 0xFE, 0xFF });
			return Preamble;
		}
		else
		{
			static Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Preamble =
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte>({ 0xFF, 0xFE });
			return Preamble;
		}
	}
	else
	{
		static Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Preamble =
			Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(0);
		return Preamble;
	}
}

const Elysium::Core::uint32_t Elysium::Core::Text::UTF16Encoding::GetByteCount(const char8_t * Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	Elysium::Core::uint32_t CodePoint;
	Elysium::Core::uint32_t Result = static_cast<Elysium::Core::uint32_t>(AdditionalCount);

	for (Elysium::Core::size i = 0; i < CharCount; ++i)
	{
		if (Input[i] >> 7 == 0x00)
		{	// 0-xxx xxxx											07 bit
			Result += 2;
		}
		else if (Input[i] >> 5 == 0x06)
		{	// 110-x xxyy	10-yy yyyy								11 bit
			Result += 2;
			i++;
		}
		else if (Input[i] >> 4 == 0x0E)
		{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
			CodePoint = ((((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F)) << 8) |
				(((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F);
			if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
			{
				Result += 4;
				i += 3;
			}
			else
			{
				Result += 2;
				i += 2;
			}
		}
		else if (Input[i] >> 3 == 0x1E)
		{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
			Result += 4;
			i += 3;
		}
		else
		{	// ToDo
			throw 1;
		}
	}

	return Result;
}

Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Text::UTF16Encoding::GetBytes(const char8_t * Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	const Elysium::Core::uint32_t RequiredSize = GetByteCount(Input, CharCount, AdditionalCount);
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Result = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(RequiredSize, AdditionalCount > 0 ? true : false);

	Elysium::Core::uint32_t CodePoint;
	Elysium::Core::byte* CodePointBytes;
	Elysium::Core::size TargetIndex = 0;
	if (_BigEndian)
	{	// 0x00 would be first byte
		for (Elysium::Core::size i = 0; i < CharCount; ++i)
		{
			if (Input[i] >> 7 == 0x00)
			{	// 0-xxx xxxx											07 bit
				Result[TargetIndex] = 0x00;
				Result[++TargetIndex] = Input[i];
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxyy	10-yy yyyy								11 bit
				Result[TargetIndex] = (Input[i] >> 2) & 0x07;
				Result[++TargetIndex] = ((Input[i] & 0x03) << 6) | (Input[++i] & 0x3F);
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
				CodePoint = ((((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F)) << 8) |
					(((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					/*
					U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
					W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
					W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
					*/
					CodePoint -= 0x10000;
					CodePointBytes = (Elysium::Core::byte*)&CodePoint;

					Result[TargetIndex] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
					Result[++TargetIndex] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
					Result[++TargetIndex] = 0xDC | (CodePointBytes[1] & 0x03);
					Result[++TargetIndex] = CodePointBytes[0];
					i += 3;
				}
				else
				{
					CodePointBytes = (Elysium::Core::byte*)&CodePoint;
					Result[TargetIndex] = CodePointBytes[1];
					Result[++TargetIndex] = CodePointBytes[0];
					i += 2;
				}
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
				CodePoint = ((((Input[i] & 0x07) << 2) | ((Input[i + 1] >> 4) & 0x03)) << 16) |
					((((Input[i + 1] & 0x0F) << 4) | ((Input[i + 2] >> 2) & 0x0F)) << 8) |
					(((Input[i + 2] & 0x03) << 6) | (Input[i + 3] & 0x3F));
				/*
				U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
				W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
				W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
				*/
				CodePoint -= 0x10000;
				CodePointBytes = (Elysium::Core::byte*)&CodePoint;

				Result[TargetIndex] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
				Result[++TargetIndex] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
				Result[++TargetIndex] = 0xDC | (CodePointBytes[1] & 0x03);
				Result[++TargetIndex] = CodePointBytes[0];
				i += 3;
			}
			else
			{	// ToDo
				throw 1;
			}
			TargetIndex++;
		}
	}
	else
	{
		for (Elysium::Core::size i = 0; i < CharCount; ++i)
		{
			if (Input[i] >> 7 == 0x00)
			{	// 0-xxx xxxx											07 bit
				Result[TargetIndex] = Input[i];
				Result[++TargetIndex] = 0x00;
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxxx	10-xx xyyy								11 bit
				Result[TargetIndex] = ((Input[i] & 0x03) << 6) | (Input[i + 1] & 0x3F);
				Result[++TargetIndex] = (Input[i] >> 2) & 0x07;
				i++;
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
				CodePoint = ((((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F)) << 8) |
					(((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F);
				if (CodePoint >= 0xD800 && CodePoint <= 0xDBFF)
				{
					/*
					U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
					W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
					W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
					*/
					CodePoint -= 0x10000;
					CodePointBytes = (Elysium::Core::byte*)&CodePoint;

					Result[TargetIndex] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
					Result[++TargetIndex] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
					Result[++TargetIndex] = CodePointBytes[0];
					Result[++TargetIndex] = 0xDC | (CodePointBytes[1] & 0x03);
					i += 3;
				}
				else
				{
					CodePointBytes = (Elysium::Core::byte*)&CodePoint;
					Result[TargetIndex] = CodePointBytes[0];
					Result[++TargetIndex] = CodePointBytes[1];
					i += 2;
				}
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
				CodePoint = ((((Input[i] & 0x07) << 2) | ((Input[i + 1] >> 4) & 0x03)) << 16) |
					((((Input[i + 1] & 0x0F) << 4) | ((Input[i + 2] >> 2) & 0x0F)) << 8) |
					(((Input[i + 2] & 0x03) << 6) | (Input[i + 3] & 0x3F));
				/*
				U' = zzzz zzzz	xxxx xxyy	.... aabb .... ....  // U - 0x10000
				W1 = 1101 10aa	bbxx xxxx      // 0xD800 + yyyyyyyyyy
				W2 = 1101 11yy	zzzz zzzz      // 0xDC00 + xxxxxxxxxx
				*/
				CodePoint -= 0x10000;
				CodePointBytes = (Elysium::Core::byte*)&CodePoint;

				Result[TargetIndex] = ((CodePointBytes[2] & 0x03) << 6) | CodePointBytes[1] >> 2;
				Result[++TargetIndex] = 0xD8 | ((CodePointBytes[2] >> 2) & 0x03);
				Result[++TargetIndex] = CodePointBytes[0];
				Result[++TargetIndex] = 0xDC | (CodePointBytes[1] & 0x03);
				i += 3;
			}
			else
			{	// ToDo
				throw 1;
			}
			TargetIndex++;
		}
	}

	return Result;
}

const Elysium::Core::uint32_t Elysium::Core::Text::UTF16Encoding::GetCharCount(const Elysium::Core::byte * Bytes, const Elysium::Core::size ByteCount) const
{
	if (ByteCount == 0)
	{
		return 0;
	}

	if (ByteCount % sizeof(char16_t) != 0)
	{	// ToDo
		throw 1;
	}
	
	const Elysium::Core::uint16_t Int16Max = Elysium::Core::UInt16::GetMaxValue();
	Elysium::Core::uint16_t SomeSurrogate;
	Elysium::Core::uint16_t LowSurrogate;
	Elysium::Core::uint32_t CodePoint;

	Elysium::Core::uint32_t Result = 0;

	if (_BigEndian)
	{	// 0x00 would be first byte
		for (Elysium::Core::size i = 0; i < ByteCount; ++i)
		{
			SomeSurrogate = Elysium::Core::uint16_t(Bytes[i] << 8 | Bytes[i + 1]);

			// check #1: are we dealing with a high surrogate? this is independent of byte order (BE/LE) ie. the high surrogate will always come first
			if (SomeSurrogate >= 0xD800 && SomeSurrogate <= 0xDBFF)
			{	// yes	(55296 - 56319)
				LowSurrogate = Elysium::Core::uint16_t(Bytes[i + 2] << 8 | Bytes[i + 3]);
				i += 3;

				CodePoint = 0x10000;
				CodePoint += (SomeSurrogate & 0x03FF) << 10;
				CodePoint += (LowSurrogate & 0x03FF);
			}
			else
			{	// no -> BMP (Basic Multilingual Plane)
				i++;

				CodePoint = SomeSurrogate;
			}

			// this would be the number of bytes required
			if (CodePoint < 0x80)			// 0 - 127
			{
				Result++;
			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{
				Result += 2;
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{
				Result += 3;
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				Result += 4;
			}
			else
			{	// ToDo
				throw 1;
			}
		}
	}
	else
	{	// 0x00 would be second byte
		for (Elysium::Core::size i = 0; i < ByteCount; ++i)
		{
			SomeSurrogate = Elysium::Core::uint16_t(Bytes[i + 1] << 8 | Bytes[i]);

			// check #1: are we dealing with a high surrogate? this is independent of byte order (BE/LE) ie. the high surrogate will always come first
			if (SomeSurrogate >= 0xD800 && SomeSurrogate <= 0xDBFF)
			{	// yes
				LowSurrogate = Elysium::Core::uint16_t(Bytes[i + 3] << 8 | Bytes[i + 2]);
				i += 3;

				CodePoint = 0x10000;
				CodePoint += (SomeSurrogate & 0x03FF) << 10;
				CodePoint += (LowSurrogate & 0x03FF);
			}
			else
			{	// no -> BMP (Basic Multilingual Plane)
				i++;

				CodePoint = SomeSurrogate;
			}

			// this would be the number of bytes required
			if (CodePoint < 0x80)			// 0 - 127
			{
				Result++;
			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{
				Result += 2;
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{
				Result += 3;
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				Result += 4;
			}
			else
			{	// ToDo
				throw 1;
			}
		}
	}

	return Result;
}

Elysium::Core::String Elysium::Core::Text::UTF16Encoding::GetString(const Elysium::Core::byte * Bytes, const Elysium::Core::size ByteCount) const
{
	const Elysium::Core::uint32_t RequiredSize = GetCharCount(Bytes, ByteCount);
	Elysium::Core::String Result = Elysium::Core::String(RequiredSize);

	constexpr const Elysium::Core::uint16_t Int16Max = Elysium::Core::UInt16::GetMaxValue();
	Elysium::Core::uint16_t SomeSurrogate;
	Elysium::Core::uint16_t LowSurrogate;
	Elysium::Core::uint32_t CodePoint;

	Elysium::Core::byte* Byte1 = nullptr;
	Elysium::Core::byte* Byte2 = nullptr;
	Elysium::Core::byte* Byte3 = nullptr;
	Elysium::Core::uint32_t CharacterIndex = 0;

	if (_BigEndian)
	{	// 0x00 would be first byte
		for (Elysium::Core::size i = 0; i < ByteCount; ++i)
		{
			SomeSurrogate = Elysium::Core::uint16_t(Bytes[i] << 8 | Bytes[i + 1]);

			// check #1: are we dealing with a high surrogate? this is independent of byte order (BE/LE) ie. the high surrogate will always come first
			if (SomeSurrogate >= 0xD800 && SomeSurrogate <= 0xDBFF)
			{	// yes
				LowSurrogate = Elysium::Core::uint16_t(Bytes[i + 2] << 8 | Bytes[i + 3]);
				i += 3;

				CodePoint = 0x10000;
				CodePoint += (SomeSurrogate & 0x03FF) << 10;
				CodePoint += (LowSurrogate & 0x03FF);
			}
			else
			{	// no -> BMP (Basic Multilingual Plane)
				i++;

				CodePoint = SomeSurrogate;
			}

			if (CodePoint < 0x80)			// 0 - 127
			{
				// 0xxx xxxx									->	0xxx xxxx
				Result[CharacterIndex++] = static_cast<Elysium::Core::uint8_t>(CodePoint);
			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{
				// 0000 0yyy	yyxx xxxx						->	110y yyyy	10xx xxxx
				Byte1 = (Elysium::Core::byte*)&CodePoint;
				Byte2 = &Byte1[1];

				Result[CharacterIndex++] = 0xC0 | (*Byte2 << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{
				// zzzz yyyy	yyxx xxxx						->	1110 zzzz	10yy yyyy	10xx xxxx
				Byte1 = (Elysium::Core::byte*)&CodePoint;
				Byte2 = &Byte1[1];

				Result[CharacterIndex++] = 0xE0 | (*Byte2 >> 4);
				Result[CharacterIndex++] = 0x80 | ((*Byte2 & 0x0F) << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				// 000a aazz	zzzz yyyy	yyxx xxxx			->	1111 0aaa	10zz zzzz	10yy yyyyy	10xx xxxx
				Byte1 = (Elysium::Core::byte*)&CodePoint;
				Byte2 = &Byte1[1];
				Byte3 = &Byte1[2];

				Result[CharacterIndex++] = 0xF0 | ((*Byte3 & 0x1F) >> 2);
				Result[CharacterIndex++] = 0x80 | ((*Byte3 & 0x03) << 4) | (*Byte2 >> 4);
				Result[CharacterIndex++] = 0x80 | ((*Byte2 & 0x0F) << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
			}
			else
			{	// ToDo
				throw 1;
			}
		}
	}
	else
	{	// 0x00 would be second byte
		for (Elysium::Core::size i = 0; i < ByteCount; ++i)
		{
			SomeSurrogate = Elysium::Core::uint16_t(Bytes[i + 1] << 8 | Bytes[i]);

			// check #1: are we dealing with a high surrogate? this is independent of byte order (BE/LE) ie. the high surrogate will always come first
			if (SomeSurrogate >= 0xD800 && SomeSurrogate <= 0xDBFF)
			{	// yes
				LowSurrogate = Elysium::Core::uint16_t(Bytes[i + 3] << 8 | Bytes[i + 2]);
				i += 3;

				CodePoint = 0x10000;
				CodePoint += (SomeSurrogate & 0x03FF) << 10;
				CodePoint += (LowSurrogate & 0x03FF);
			}
			else
			{	// no -> BMP (Basic Multilingual Plane)
				i++;

				CodePoint = SomeSurrogate;
			}

			if (CodePoint < 0x80)			// 0 - 127
			{
				// 0xxx xxxx									->	0xxx xxxx
				Result[CharacterIndex++] = static_cast<Elysium::Core::uint8_t>(CodePoint);
			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{
				// 0000 0yyy	yyxx xxxx						->	110y yyyy	10xx xxxx
				Byte1 = (Elysium::Core::byte*)&CodePoint;
				Byte2 = &Byte1[1];

				Result[CharacterIndex++] = 0xC0 | (*Byte2 << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{
				// zzzz yyyy	yyxx xxxx						->	1110 zzzz	10yy yyyy	10xx xxxx
				Byte1 = (Elysium::Core::byte*)&CodePoint;
				Byte2 = &Byte1[1];

				Result[CharacterIndex++] = 0xE0 | (*Byte2 >> 4);
				Result[CharacterIndex++] = 0x80 | ((*Byte2 & 0x0F) << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				// 000a aazz	zzzz yyyy	yyxx xxxx			->	1111 0aaa	10zz zzzz	10yy yyyyy	10xx xxxx
				Byte1 = (Elysium::Core::byte*)&CodePoint;
				Byte2 = &Byte1[1];
				Byte3 = &Byte1[2];

				Result[CharacterIndex++] = 0xF0 | ((*Byte3 & 0x1F) >> 2);
				Result[CharacterIndex++] = 0x80 | ((*Byte3 & 0x03) << 4) | (*Byte2 >> 4);
				Result[CharacterIndex++] = 0x80 | ((*Byte2 & 0x0F) << 2) | (*Byte1 >> 6);
				Result[CharacterIndex++] = 0x80 | (*Byte1 & 0x3F);
			}
			else
			{	// ToDo
				throw 1;
			}
		}
	}

	return Result;
}
