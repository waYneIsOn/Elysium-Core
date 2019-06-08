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

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_URISYNTAXFLAGS
#include "UriSyntaxFlags.hpp"
#endif

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

			std::map<String, UriParser*> Map;
		};
	}
}
#endif
