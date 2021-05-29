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
#include "Primitives.hpp"
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

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_DICTIONARY
#include "Dictionary.hpp"
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

		UriParser& operator=(const UriParser& Source) = delete;
		UriParser& operator=(UriParser&& Right) noexcept = delete;

		static const bool IsKnownScheme(const Elysium::Core::String& SchemeName);
		static const bool IsKnownScheme(const Elysium::Core::StringView& SchemeName);

		static void Register(const Elysium::Core::UriParser& UriParser, const Elysium::Core::String& SchemeName, const Elysium::Core::uint16_t DefaultPort);





		Elysium::Core::StringView ParseComponent(const Elysium::Core::UriComponents Component, const Elysium::Core::String& Source);
	protected:
		UriParser(const Elysium::Core::String& Scheme, int Port, Elysium::Core::UriSyntaxFlags RequiredComponents);

		//virtual Elysium::Core::StringView GetComponents(...);
	private:
		static const Elysium::Core::UriSyntaxFlags _DummySyntaxFlags;
		static const Elysium::Core::UriSyntaxFlags _HttpSyntaxFlags;

		//static Elysium::Core::Collections::Template::Dictionary<Elysium::Core::String, Elysium::Core::UriParser> _RegisteredParser;
		
		Elysium::Core::String _Scheme;
		Elysium::Core::uint32_t _Port;
		Elysium::Core::UriSyntaxFlags _RequiredComponents;
	};
}
#endif
