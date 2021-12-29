/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_URIPARSER
#define ELYSIUM_CORE_URIPARSER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_URICOMPONENTS
#include "UriComponents.hpp"
#endif

#ifndef ELYSIUM_CORE_URISYNTAXFLAGS
#include "UriSyntaxFlags.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Uri;

	class ELYSIUM_CORE_API UriParser
	{
	public:
		UriParser(const UriParser& Source) = delete;

		UriParser(UriParser&& Right) noexcept = delete;

		virtual ~UriParser();
	public:
		UriParser& operator=(const UriParser& Source) = delete;

		UriParser& operator=(UriParser&& Right) noexcept = delete;
	public:
		static const bool IsKnownScheme(const Elysium::Core::Utf8String& SchemeName);

		static const bool IsKnownScheme(const Elysium::Core::Utf8StringView& SchemeName);

		static void Register(const Elysium::Core::UriParser& UriParser, const Elysium::Core::Utf8String& SchemeName, const Elysium::Core::uint16_t DefaultPort);





		Elysium::Core::Utf8StringView ParseComponent(const Elysium::Core::UriComponents Component, const Elysium::Core::Utf8String& Source);
	protected:
		UriParser(const Elysium::Core::Utf8String& Scheme, int Port, Elysium::Core::UriSyntaxFlags RequiredComponents);

		//virtual Elysium::Core::Utf8StringView GetComponents(...);
	private:
		static const Elysium::Core::UriSyntaxFlags _DummySyntaxFlags;
		static const Elysium::Core::UriSyntaxFlags _HttpSyntaxFlags;

		//static Elysium::Core::Collections::Template::Dictionary<Elysium::Core::Utf8String, Elysium::Core::UriParser> _RegisteredParser;
		
		Elysium::Core::Utf8String _Scheme;
		Elysium::Core::uint32_t _Port;
		Elysium::Core::UriSyntaxFlags _RequiredComponents;
	};
}
#endif
