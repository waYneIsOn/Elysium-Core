/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEXT_UTF32ENCODING
#define ELYSIUM_CORE_TEXT_UTF32ENCODING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "Encoding.hpp"
#endif

namespace Elysium::Core::Text
{
	class ELYSIUM_CORE_API UTF32Encoding final : public Encoding
	{
	public:
		UTF32Encoding();
		UTF32Encoding(const bool BigEndian, const bool EncoderShouldEmitIdentifier, const bool ThrowOnInvalidBytes);
		UTF32Encoding(const UTF32Encoding& Source) = delete;
		UTF32Encoding(UTF32Encoding&& Right) noexcept = delete;
		virtual ~UTF32Encoding();

		UTF32Encoding& operator=(const UTF32Encoding& Source) = delete;
		UTF32Encoding& operator=(UTF32Encoding&& Right) noexcept = delete;

		virtual const bool GetIsSingleByte() const override;

		virtual const Elysium::Core::String& GetEncodingName() const override;

		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& GetPreamble() const override;

		virtual const Elysium::Core::uint32_t GetByteCount(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount) const override;

		virtual Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetBytes(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount = 0) const override;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const override;

		virtual Elysium::Core::String GetString(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const override;
	private:
		const bool _BigEndian;	// 0x00 will be the first byte
		const bool _EncoderShouldEmitIdentifier;
		const bool _ThrowOnInvalidBytes;
	};
}
#endif
