/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEXT_UTF16ENCODING
#define ELYSIUM_CORE_TEXT_UTF16ENCODING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "Encoding.hpp"
#endif

namespace Elysium::Core::Text
{
	/*
	class ELYSIUM_CORE_API UTF16Encoding final : public Encoding
	{
	public:
		UTF16Encoding();
		UTF16Encoding(bool BigEndian, bool EncoderShouldEmitUTF8Identifier, bool ThrowOnInvalidBytes);
		UTF16Encoding(const UTF16Encoding& Source) = delete;
		UTF16Encoding(UTF16Encoding&& Right) noexcept = delete;
		virtual ~UTF16Encoding();

		UTF16Encoding& operator=(const UTF16Encoding& Source) = delete;
		UTF16Encoding& operator=(UTF16Encoding&& Right) noexcept = delete;

		virtual const bool GetIsSingleByte() const override;
		virtual const String GetEncodingName() const override;

		virtual const Elysium::Core::uint32_t GetByteCount(const Elysium::Core::String& Input, const size_t CharIndex, const size_t CharCount) const override;

		virtual Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetBytes(const Elysium::Core::String& Input, const size_t CharIndex, const size_t CharCount) const override;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const size_t ByteCount) const override;

		virtual Elysium::Core::String GetString(const Elysium::Core::byte* Bytes, const size_t ByteCount) const override;
	private:
		const bool _EncoderShouldEmitUTF8Identifier;
		const bool _ThrowOnInvalidBytes;

		static const Collections::Template::Array<Elysium::Core::byte> _BOM;
	};
	*/
}
#endif