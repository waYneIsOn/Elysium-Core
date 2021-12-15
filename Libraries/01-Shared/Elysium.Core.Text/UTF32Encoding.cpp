#include "UTF32Encoding.hpp"

#ifndef ELYSIUM_CORE_SYSTEM
#include "../Elysium.Core/System.hpp"
#endif

Elysium::Core::Text::UTF32Encoding::UTF32Encoding()
	: Elysium::Core::Text::UTF32Encoding(false, false, false)
{ }
Elysium::Core::Text::UTF32Encoding::UTF32Encoding(const bool BigEndian, const bool EncoderShouldEmitIdentifier, const bool ThrowOnInvalidBytes)
	: Elysium::Core::Text::Encoding(BigEndian ? 12001 : 12000),
	_BigEndian(BigEndian), _EncoderShouldEmitIdentifier(EncoderShouldEmitIdentifier), _ThrowOnInvalidBytes(ThrowOnInvalidBytes)
{ }
Elysium::Core::Text::UTF32Encoding::~UTF32Encoding()
{ }

const bool Elysium::Core::Text::UTF32Encoding::GetIsSingleByte() const
{
	return false;
}

const Elysium::Core::String& Elysium::Core::Text::UTF32Encoding::GetEncodingName() const
{
	if (_BigEndian)
	{
		static Elysium::Core::String EncodingName = u8"Unicode (UTF-32 Big-Endian)";
		return EncodingName;
	}
	else
	{
		static Elysium::Core::String EncodingName = u8"Unicode (UTF-32 Little-Endian)";
		return EncodingName;
	}
}

const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Elysium::Core::Text::UTF32Encoding::GetPreamble() const
{
	if (_EncoderShouldEmitIdentifier)
	{
		if (_BigEndian)
		{
			static Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Preamble =
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte>({ 0x00, 0x00, 0xFE, 0xFF });
			return Preamble;
		}
		else
		{
			static Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Preamble =
				Elysium::Core::Collections::Template::Array<Elysium::Core::byte>({ 0xFF, 0xFE, 0x00, 0x00 });
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

const Elysium::Core::uint32_t Elysium::Core::Text::UTF32Encoding::GetByteCount(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	Elysium::Core::uint32_t Result = static_cast<Elysium::Core::uint32_t>(AdditionalCount);

	for (Elysium::Core::size i = 0; i < CharCount; ++i)
	{
		if (Input[i] >> 7 == 0x00)
		{	// 0-xxx xxxx											07 bit
			Result += 4;
		}
		else if (Input[i] >> 5 == 0x06)
		{	// 110-x xxyy	10-yy yyyy								11 bit
			Result += 4;
			i++;
		}
		else if (Input[i] >> 4 == 0x0E)
		{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
			Result += 4;
			i += 2;
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

Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Elysium::Core::Text::UTF32Encoding::GetBytes(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const
{
	const Elysium::Core::uint32_t RequiredSize = GetByteCount(Input, CharCount, AdditionalCount);
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Result = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(RequiredSize, AdditionalCount > 0 ? true : false);
	
	Elysium::Core::size TargetIndex = 0;
	if (_BigEndian)
	{	// 0x00 would be first byte
		for (Elysium::Core::size i = 0; i < CharCount; ++i)
		{
			if (Input[i] >> 7 == 0x00)
			{	// 0-xxx xxxx											07 bit
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Result[TargetIndex++] = Input[i];
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
#else
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = Input[i];
#endif
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxyy	10-yy yyyy								11 bit
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Result[TargetIndex++] = (Input[i] >> 2) & 0x07;
				Result[TargetIndex++] = ((Input[i] & 0x03) << 6) | (Input[++i] & 0x3F);
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
#else
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#endif
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Result[TargetIndex++] = (((Input[i] & 0x0F) << 4) | ((Input[i + 1] >> 2) & 0x0F));
				Result[TargetIndex++] = ((Input[i + 1] & 0x03) << 6) | Input[i + 2] & 0x3F;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
#else
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#endif
				i += 2;
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Result[TargetIndex++] = (((Input[i] & 0x07) << 2) | ((Input[i + 1] >> 4) & 0x03));
				Result[TargetIndex++] = (((Input[i + 1] & 0x0F) << 4) | ((Input[i + 2] >> 2) & 0x0F));
				Result[TargetIndex++] = ((Input[i + 2] & 0x03) << 6) | (Input[i + 3] & 0x3F);
				Result[TargetIndex++] = 0x00;
#else
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#endif
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
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = Input[i];
#else
				Result[TargetIndex++] = Input[i];
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#endif
			}
			else if (Input[i] >> 5 == 0x06)
			{	// 110-x xxxx	10-xx xyyy								11 bit
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Result[TargetIndex++] = ((Input[i] & 0x03) << 6) | (Input[i + 1] & 0x3F);
				Result[TargetIndex++] = (Input[i] >> 2) & 0x07;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#else
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#endif
				i++;
			}
			else if (Input[i] >> 4 == 0x0E)
			{	// 1110 xxxx	10-xx xxyy	10-yy yyyy					16 bit
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#else
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#endif
				i += 2;
			}
			else if (Input[i] >> 3 == 0x1E)
			{	// 1111 0-xxx	10-xx yyyy	10-yy yyzz	10-zz zzzz		21 bit
#if defined ELYSIUM_CORE_LITTLEENDIAN
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#else
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;
				Result[TargetIndex++] = 0x00;

				throw 1;
#endif
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

const Elysium::Core::uint32_t Elysium::Core::Text::UTF32Encoding::GetCharCount(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const
{
	if (ByteCount == 0)
	{
		return 0;
	}

	if (ByteCount % sizeof(char32_t) != 0)
	{	// ToDo
		throw 1;
	}

	Elysium::Core::uint32_t CodePoint;

	Elysium::Core::uint32_t Result = 0;

	if (_BigEndian)
	{	// 0x00 would be first byte
		for (Elysium::Core::size i = 0; i < ByteCount; ++i)
		{
			CodePoint = Elysium::Core::uint32_t(Bytes[i] << 24 | Bytes[i + 1] << 16 | Bytes[i + 2] << 8 | Bytes[i + 3]);
			if (CodePoint < 0x80)			// 0 - 127
			{
				Result++;
			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{
				i++;
				Result += 2;
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{
				i += 2;
				Result += 3;
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				i += 3;
				Result += 4;
			}
			else
			{	// ToDo
				throw 1;
			}
		}
	}
	else
	{
		for (Elysium::Core::size i = 0; i < ByteCount; ++i)
		{
			CodePoint = Elysium::Core::uint32_t(Bytes[i] | Bytes[i + 1] << 8 | Bytes[i + 2] << 16 | Bytes[i + 3] << 24);
			if (CodePoint < 0x80)			// 0 - 127
			{
				Result++;
			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{
				i++;
				Result += 2;
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{
				i += 2;
				Result += 3;
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{
				i += 3;
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

Elysium::Core::String Elysium::Core::Text::UTF32Encoding::GetString(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const
{
	const Elysium::Core::uint32_t RequiredSize = GetCharCount(Bytes, ByteCount);
	Elysium::Core::String Result = Elysium::Core::String(RequiredSize);

	Elysium::Core::uint32_t CodePoint;

	if (_BigEndian)
	{	// 0x00 would be first byte
		for (Elysium::Core::size i = 0; i < ByteCount; ++i)
		{
			CodePoint = Elysium::Core::uint32_t(Bytes[i] << 24 | Bytes[i + 1] << 16 | Bytes[i + 2] << 8 | Bytes[i + 3]);
			if (CodePoint < 0x80)			// 0 - 127
			{

			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{

				i++;
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{

				i += 2;
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{

				i += 3;
			}
			else
			{	// ToDo
				throw 1;
			}
		}
	}
	else
	{
		for (Elysium::Core::size i = 0; i < ByteCount; ++i)
		{
			CodePoint = Elysium::Core::uint32_t(Bytes[i] | Bytes[i + 1] << 8 | Bytes[i + 2] << 16 | Bytes[i + 3] << 24);
			if (CodePoint < 0x80)			// 0 - 127
			{

			}
			else if (CodePoint < 0x800)		// 128 - 2047
			{

				i++;
			}
			else if (CodePoint < 0x10000)	// 2048 - 65535
			{

				i += 2;
			}
			else if (CodePoint < 0x110000)	// 65536 - 1114111
			{

				i += 3;
			}
			else
			{	// ToDo
				throw 1;
			}
		}
	}

	return Result;
}
