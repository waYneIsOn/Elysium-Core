/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_URIPARSERTABLE
#define ELYSIUM_CORE_URIPARSERTABLE

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef _MAP_
#include <map>
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_URISYNTAXFLAGS
#include "UriSyntaxFlags.hpp"
#endif

namespace Elysium::Core
{
	/*
	class ELYSIUM_CORE_API UriParser;

	// make sure the following classes get exported (warning C4251)
	template class ELYSIUM_CORE_API std::map<String, UriParser*>;
	//template struct ELYSIUM_CORE_API std::pair<String, UriParser*>;
	//template class ELYSIUM_CORE_API std::allocator<std::pair<String, UriParser*>>;

	class ELYSIUM_CORE_API UriParserTable final
	{
	public:
		UriParserTable();
		~UriParserTable();

		std::map<String, UriParser*> Map;
	};
	*/
}
#endif
