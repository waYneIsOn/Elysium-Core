/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

		virtual String GetString(const byte* Bytes, const size_t ByteCount) const override;
	private:
		//static const Elysium::Core::Collections::Template::Array<char16_t> _Chart;
	};
}
#endif
