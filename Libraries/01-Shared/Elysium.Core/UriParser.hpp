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

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_URICOMPONENTS
#include "UriComponents.hpp"
#endif

#ifndef ELYSIUM_CORE_URISYNTAXFLAGS
#include "UriSyntaxFlags.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Uri;

	class ELYSIUM_CORE_API UriParser
	{
	public:
		virtual ~UriParser() = 0;

		static void Register(UriParser& UriParser, const String& SchemeName, int DefaultPort);

		void ParseComponent(UriComponents Component, const String& Source, StringView& Output);
	protected:
		UriParser(const String& Scheme, int Port, UriSyntaxFlags RequiredComponents);
	private:
		friend class Uri;
		friend class UriParserTable;

		static UriSyntaxFlags DummySyntaxFlags;
		static UriSyntaxFlags HttpSyntaxFlags;

		String _Scheme;
		int _Port;
		UriSyntaxFlags _RequiredComponents;
	};
}
#endif
