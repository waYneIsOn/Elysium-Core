/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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
		UTF8Encoding(bool EncoderShouldEmitUTF8Identifier);
		UTF8Encoding(const UTF8Encoding& Source) = delete;
		UTF8Encoding(UTF8Encoding&& Right) noexcept = delete;
		virtual ~UTF8Encoding();

		UTF8Encoding& operator=(const UTF8Encoding& Source) = delete;
		UTF8Encoding& operator=(UTF8Encoding&& Right) noexcept = delete;

		virtual const bool GetIsSingleByte() const override;
		virtual const String GetEncodingName() const override;

		virtual Elysium::Core::Collections::Template::List<byte> GetBytes(const char16_t Input) const override;
		virtual Elysium::Core::Collections::Template::List<byte> GetBytes(const String& Input, const size_t CharIndex, const size_t CharCount) const override;

		virtual String GetString(const byte* Bytes, const size_t ByteCount) const override;
	private:
		bool _EncoderShouldEmitUTF8Identifier;
	};
}
#endif
