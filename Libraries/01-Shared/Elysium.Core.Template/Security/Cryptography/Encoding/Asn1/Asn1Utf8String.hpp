/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UTF8STRING
#define ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1UTF8STRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SECURITY_CRYPTOGRAPHY_ENCODING_ASN1_ASN1IDENTIFIER
#include "Asn1Identifier.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../System/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRINGVIEW
#include "../../../../Text/StringView.hpp"
#endif

namespace Elysium::Core::Template::Security::Cryptography::Encoding::Asn1
{
	class Asn1Utf8String
	{
	public:
		constexpr Asn1Utf8String() = delete;
		
		inline constexpr Asn1Utf8String(const Asn1Identifier& Identifier, const char8_t* Data, const Elysium::Core::Template::System::size Length)
			: _Identifier(Identifier), _Value(Data, Length)
		{ }
		
		inline constexpr Asn1Utf8String(const Asn1Identifier& Identifier, const Elysium::Core::Template::Text::StringView<char8_t> Value)
			: _Identifier(Identifier), _Value(Value)
		{ }

		constexpr Asn1Utf8String(const Asn1Utf8String& Source) = delete;

		constexpr Asn1Utf8String(Asn1Utf8String&& Right) noexcept = delete;

		constexpr ~Asn1Utf8String() = default;
	public:
		constexpr Asn1Utf8String& operator=(const Asn1Utf8String& Source) = delete;

		constexpr Asn1Utf8String& operator=(Asn1Utf8String&& Right) noexcept = delete;
	public:
		inline constexpr const Asn1Identifier& GetIdentifier() const
		{
			return _Identifier;
		}

		inline constexpr const Elysium::Core::Template::Text::String<char8_t>& GetValue() const
		{
			return _Value;
		}
	private:
		Asn1Identifier _Identifier;
		Elysium::Core::Template::Text::String<char8_t> _Value;
	};
}
#endif
