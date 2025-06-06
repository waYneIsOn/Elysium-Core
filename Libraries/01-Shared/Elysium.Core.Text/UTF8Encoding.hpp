/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEXT_UTF8ENCODING
#define ELYSIUM_CORE_TEXT_UTF8ENCODING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "Encoding.hpp"
#endif

namespace Elysium::Core::Text
{
	class ELYSIUM_CORE_API UTF8Encoding final : public Encoding
	{
	public:
		UTF8Encoding();

		UTF8Encoding(const bool EncoderShouldEmitIdentifier, const bool ThrowOnInvalidBytes);

		UTF8Encoding(const UTF8Encoding& Source) = delete;

		UTF8Encoding(UTF8Encoding&& Right) noexcept = delete;

		virtual ~UTF8Encoding();
	public:
		UTF8Encoding& operator=(const UTF8Encoding& Source) = delete;

		UTF8Encoding& operator=(UTF8Encoding&& Right) noexcept = delete;
	public:
		virtual const bool GetIsSingleByte() const override;

		virtual const Elysium::Core::Utf8String& GetEncodingName() const override;

		virtual const Elysium::Core::Container::VectorOfByte& GetPreamble() const override;
	public:
		virtual const Elysium::Core::uint32_t GetByteCount(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount = 0) const override;

		virtual Elysium::Core::Container::VectorOfByte GetBytes(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount = 0) const override;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const override;

		virtual Elysium::Core::Utf8String GetString(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const override;
	private:
		const bool _EncoderShouldEmitIdentifier;
		const bool _ThrowOnInvalidBytes;
	};
}
#endif
