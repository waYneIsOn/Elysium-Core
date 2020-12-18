/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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
	class ELYSIUM_CORE_API UTF16Encoding final : public Encoding
	{
	public:
		UTF16Encoding();
		UTF16Encoding(const bool BigEndian, const bool EncoderShouldEmitIdentifier, const bool ThrowOnInvalidBytes);
		UTF16Encoding(const UTF16Encoding& Source) = delete;
		UTF16Encoding(UTF16Encoding&& Right) noexcept = delete;
		virtual ~UTF16Encoding();

		UTF16Encoding& operator=(const UTF16Encoding& Source) = delete;
		UTF16Encoding& operator=(UTF16Encoding&& Right) noexcept = delete;

		virtual const bool GetIsSingleByte() const override;

		virtual const Elysium::Core::String GetEncodingName() const override;

		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetPreamble() const override;

		virtual const Elysium::Core::uint32_t GetByteCount(const char8_t* Input, const size_t CharCount, const size_t AdditionalCount) const override;

		virtual Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetBytes(const char8_t* Input, const size_t CharCount, const size_t AdditionalCount = 0) const override;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const size_t ByteCount) const override;

		virtual Elysium::Core::String GetString(const Elysium::Core::byte* Bytes, const size_t ByteCount) const override;
	private:
		const bool _BigEndian;	// 0x00 will be the first byte
		const bool _EncoderShouldEmitIdentifier;
		const bool _ThrowOnInvalidBytes;
	};
}
#endif
