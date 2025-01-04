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
	public:
		ASCIIEncoding& operator=(const ASCIIEncoding& Source) = delete;

		ASCIIEncoding& operator=(ASCIIEncoding&& Right) noexcept = delete;
	public:
		virtual const bool GetIsSingleByte() const override;

		virtual const Elysium::Core::Utf8String& GetEncodingName() const override;

		virtual const Elysium::Core::Container::VectorOfByte& GetPreamble() const override;
	public:
		virtual const Elysium::Core::uint32_t GetByteCount(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount = 0) const override;

		virtual Elysium::Core::Container::VectorOfByte GetBytes(const char8_t* Input, const Elysium::Core::size CharCount, const Elysium::Core::size AdditionalCount = 0) const override;

		virtual const Elysium::Core::uint32_t GetCharCount(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const override;

		virtual Elysium::Core::Utf8String GetString(const Elysium::Core::byte* Bytes, const Elysium::Core::size ByteCount) const override;
	};
}
#endif
