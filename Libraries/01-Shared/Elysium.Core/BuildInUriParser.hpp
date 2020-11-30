/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_BUILDINURIPARSER
#define ELYSIUM_CORE_BUILDINURIPARSER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_URIPARSER
#include "UriParser.hpp"
#endif

namespace Elysium::Core
{
	class BuildInUriParser : public UriParser
	{
	public:
		BuildInUriParser(String Scheme, int Port, UriSyntaxFlags RequiredComponents);
	};
}
#endif
