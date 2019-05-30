/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_URIPARSER
#define ELYSIUM_CORE_URIPARSER

#ifndef _XSTRING_
#include <string>
#include <string_view>
#endif

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
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

		class EXPORT UriParser
		{
		public:
			virtual ~UriParser() = 0;

			static void Register(UriParser* UriParser, std::string SchemeName, int DefaultPort);

			virtual std::string_view ParseComponent(UriComponents Component, std::string* const Source);
		protected:
			UriParser(std::string Scheme, int Port, UriSyntaxFlags RequiredComponents);
		private:
			friend class Uri;
			friend class UriParserTable;

			static UriSyntaxFlags DummySyntaxFlags;
			static UriSyntaxFlags HttpSyntaxFlags;

			static UriParserTable _ParserTable;

			std::string _Scheme;
			int _Port;
			UriSyntaxFlags _RequiredComponents;
		};
	}
}
#endif
