/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEXT_ENCODING
#define ELYSIUM_CORE_TEXT_ENCODING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../Elysium.Core/ArrayOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

namespace Elysium::Core::Text
{
	class ELYSIUM_CORE_API ASCIIEncoding;
	class ELYSIUM_CORE_API UTF7Encoding;
	class ELYSIUM_CORE_API UTF8Encoding;
	class ELYSIUM_CORE_API UTF16Encoding;
	class ELYSIUM_CORE_API UTF32Encoding;

	class ELYSIUM_CORE_API Encoding
	{
	public:
		Encoding(const Encoding& Source) = delete;
		Encoding(Encoding&& Right) noexcept = delete;
		virtual ~Encoding();

		Encoding& operator=(const Encoding& Source) = delete;
		Encoding& operator=(Encoding&& Right) noexcept = delete;
	protected:
		Encoding();
		Encoding(const Elysium::Core::uint32_t CodePage);
	public:
		//static void GetEncoding(int CodePage, Encoding* Output);

		static Encoding& Default();
		static Encoding& ASCII();
		static Encoding& UTF7();
		static Encoding& UTF8();
		static Encoding& UTF16BE();
		static Encoding& UTF16LE();
		static Encoding& UTF32BE();
		static Encoding& UTF32LE();

		static const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Convert(const Encoding& SourceEncoding, const Encoding& TargetEncoding, const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Bytes, const Elysium::Core::size Index, const Elysium::Core::size Count);
				
		virtual const bool GetIsSingleByte() const = 0;

		virtual const Elysium::Core::uint32_t GetCodePage() const;

		virtual const Elysium::Core::String& GetEncodingName() const = 0;

		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& GetPreamble() const = 0;

		//virtual Elysium::Core::uint32_t GetMaxByteCount(Elysium::Core::uint32_t charCount) = 0;

		virtual const Elysium::Core::uint32_t GetByteCount(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount = 0) const = 0;

		virtual Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetBytes(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount = 0) const = 0;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const = 0;

		//virtual char8_t* GetCharArray(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const = 0;

		virtual Elysium::Core::String GetString(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const = 0;
	private:
		const Elysium::Core::uint32_t _CodePage;

		static ASCIIEncoding _ASCII;
		static UTF8Encoding _UTF8;
		static UTF16Encoding _UTF16BE;
		static UTF16Encoding _UTF16LE;
		static UTF32Encoding _UTF32BE;
		static UTF32Encoding _UTF32LE;
	};
}
#endif
