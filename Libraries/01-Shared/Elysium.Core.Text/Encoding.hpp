/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "../Elysium.Core/List.hpp"
#endif

namespace Elysium::Core::Text
{
	class ELYSIUM_CORE_API ASCIIEncoding;
	class ELYSIUM_CORE_API UnicodeEncoding;
	class ELYSIUM_CORE_API UTF32Encoding;
	class ELYSIUM_CORE_API UTF7Encoding;
	class ELYSIUM_CORE_API UTF8Encoding;

	class ELYSIUM_CORE_API Encoding
	{
	public:
		Encoding(const Encoding& Source) = delete;
		Encoding(Encoding&& Right) noexcept = delete;
		virtual ~Encoding();

		Encoding& operator=(const Encoding& Source) = delete;
		Encoding& operator=(Encoding&& Right) noexcept = delete;

		static void GetEncoding(int CodePage, Encoding* Output);

		static const Encoding& ASCII();
		static const Encoding& BigEndianUnicode();	// UTF-16 big-endian
		static const Encoding& Default();
		static const Encoding& Unicode();	// UTF-16 little-endian
		static const Encoding& UTF32();
		static const Encoding& UTF7();
		static const Encoding& UTF8();
				
		virtual const bool GetIsSingleByte() const = 0;
		virtual const int GetCodePage() const;
		virtual const Elysium::Core::String GetEncodingName() const = 0;
		//virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetPreamble() const = 0;	// BOM

		//virtual Elysium::Core::uint32_t GetMaxByteCount(Elysium::Core::uint32_t charCount) = 0;

		virtual const Elysium::Core::uint32_t GetByteCount(const Elysium::Core::String& Input, const size_t CharIndex, const size_t CharCount) const = 0;

		virtual Elysium::Core::Collections::Template::List<Elysium::Core::byte> GetBytes(const char Input) const = 0;
		virtual Elysium::Core::Collections::Template::List<Elysium::Core::byte> GetBytes(const Elysium::Core::String& Input, const size_t CharIndex, const size_t CharCount) const = 0;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const size_t ByteCount) const = 0;

		virtual Elysium::Core::String GetString(const Elysium::Core::byte* Bytes, const size_t ByteCount) const = 0;
	protected:
		Encoding();
		Encoding(int CodePage);
	private:
		int _CodePage;

		static const ASCIIEncoding _ASCII;
		static const UTF8Encoding _UTF8;
	};
}
#endif
