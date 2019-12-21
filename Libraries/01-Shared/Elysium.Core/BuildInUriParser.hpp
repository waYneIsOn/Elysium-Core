/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_BUILDINURIPARSER
#define ELYSIUM_CORE_BUILDINURIPARSER

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
