/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEXT_ASCIIENCODING
#define ELYSIUM_CORE_TEXT_ASCIIENCODING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "Encoding.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../Elysium.Core/Array.hpp"
#endif

namespace Elysium::Core::Text
{
	class ELYSIUM_CORE_API ASCIIEncoding final : public Encoding
	{
	public:
		ASCIIEncoding();
		ASCIIEncoding(const ASCIIEncoding& Source) = delete;
		ASCIIEncoding(ASCIIEncoding&& Right) noexcept = delete;
		virtual ~ASCIIEncoding();

		ASCIIEncoding& operator=(const ASCIIEncoding& Source) = delete;
		ASCIIEncoding& operator=(ASCIIEncoding&& Right) noexcept = delete;

		virtual const bool GetIsSingleByte() const override;

		virtual const Elysium::Core::String GetEncodingName() const override;

		virtual const Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetPreamble() const override;

		virtual const Elysium::Core::uint32_t GetByteCount(const char8_t* Input, const size_t CharCount, const size_t AdditionalCount = 0) const override;

		virtual Elysium::Core::Collections::Template::Array<Elysium::Core::byte> GetBytes(const char8_t* Input, const size_t CharCount, const size_t AdditionalCount = 0) const override;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const size_t ByteCount) const override;

		virtual Elysium::Core::String GetString(const Elysium::Core::byte* Bytes, const size_t ByteCount) const override;
	};
}
#endif
