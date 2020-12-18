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

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
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
	class ASCIIEncoding;
	class UTF7Encoding;
	class UTF8Encoding;
	class UTF16Encoding;
	class UTF32Encoding;

	class ELYSIUM_CORE_API Encoding
	{
	public:
		Encoding(const Encoding& Source) = delete;
		Encoding(Encoding&& Right) noexcept = delete;
		virtual ~Encoding();

		Encoding& operator=(const Encoding& Source) = delete;
		Encoding& operator=(Encoding&& Right) noexcept = delete;

		//static void GetEncoding(int CodePage, Encoding* Output);

		static const Encoding& Default();
		static const Encoding& ASCII();
		static const Encoding& UTF7();
		static const Encoding& UTF8();
		static const Encoding& UTF16BE();
		static const Encoding& UTF16LE();
		static const Encoding& UTF32BE();
		static const Encoding& UTF32LE();

		static const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Convert(const Encoding& SourceEncoding, const Encoding& TargetEncoding, const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Bytes, const size_t Index, const size_t Count);
				
		virtual const bool GetIsSingleByte() const = 0;

		virtual const Elysium::Core::uint32_t GetCodePage() const;

		virtual const Elysium::Core::String GetEncodingName() const = 0;

		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetPreamble() const = 0;

		//virtual Elysium::Core::uint32_t GetMaxByteCount(Elysium::Core::uint32_t charCount) = 0;

		virtual const Elysium::Core::uint32_t GetByteCount(const char8_t* Input, const size_t CharCount, const size_t AdditionalCount = 0) const = 0;

		virtual Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetBytes(const char8_t* Input, const size_t CharCount, const size_t AdditionalCount = 0) const = 0;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const size_t ByteCount) const = 0;

		virtual Elysium::Core::String GetString(const Elysium::Core::byte* Bytes, const size_t ByteCount) const = 0;
	protected:
		Encoding();
		Encoding(const Elysium::Core::uint32_t CodePage);
	private:
		const Elysium::Core::uint32_t _CodePage;

		static const ASCIIEncoding _ASCII;
		static const UTF8Encoding _UTF8;
		static const UTF16Encoding _UTF16BE;
		static const UTF16Encoding _UTF16LE;
		static const UTF32Encoding _UTF32BE;
		static const UTF32Encoding _UTF32LE;
	};
}
#endif
