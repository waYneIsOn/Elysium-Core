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
	/*
	class ELYSIUM_CORE_API UTF32Encoding final : public Encoding
	{
	public:
		UTF32Encoding();
		UTF32Encoding(bool BigEndian, bool EncoderShouldEmitUTF8Identifier, bool ThrowOnInvalidBytes);
		UTF32Encoding(const UTF32Encoding& Source) = delete;
		UTF32Encoding(UTF32Encoding&& Right) noexcept = delete;
		virtual ~UTF32Encoding();

		UTF32Encoding& operator=(const UTF32Encoding& Source) = delete;
		UTF32Encoding& operator=(UTF32Encoding&& Right) noexcept = delete;

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
