/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_URIPARSERTABLE
#define ELYSIUM_CORE_URIPARSERTABLE

#ifndef _MAP_
#include <map>
#endif

#ifndef _XSTRING_
#include <string>
#include <string_view>
#endif

#ifndef ELYSIUM_CORE_URISYNTAXFLAGS
#include "UriSyntaxFlags.hpp"
#endif

using std::map;
using std::string;

namespace Elysium
{
	namespace Core
	{
		class UriParser;

		class UriParserTable final
		{
		public:
			UriParserTable();
			~UriParserTable();

			map<string, UriParser*> Map;
		};
	}
}
#endif
