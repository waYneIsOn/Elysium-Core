/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_URIPARSER
#define ELYSIUM_CORE_URIPARSER
/*
#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_URICOMPONENTS
#include "UriComponents.hpp"
#endif

#ifndef ELYSIUM_CORE_URISYNTAXFLAGS
#include "UriSyntaxFlags.hpp"
#endif

#pragma warning(disable : 4251)

namespace Elysium
{
	namespace Core
	{
		class Uri;
		class UriParserTable;

		class ELYSIUM_CORE_API UriParser
		{
		public:
			virtual ~UriParser() = 0;

			static void Register(UriParser* UriParser, const String& SchemeName, int DefaultPort);

			//virtual std::string_view ParseComponent(UriComponents Component, std::string* const Source);
		protected:
			UriParser(const String& Scheme, int Port, UriSyntaxFlags RequiredComponents);
		private:
			friend class Uri;
			friend class UriParserTable;

			static UriSyntaxFlags DummySyntaxFlags;
			static UriSyntaxFlags HttpSyntaxFlags;

			static UriParserTable _ParserTable;

			String _Scheme;
			int _Port;
			UriSyntaxFlags _RequiredComponents;
		};
	}
}
*/
#endif
