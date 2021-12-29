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
	class BuildInUriParser : public Elysium::Core::UriParser
	{
	public:
		BuildInUriParser(Elysium::Core::Utf8String Scheme, int Port, UriSyntaxFlags RequiredComponents);

		BuildInUriParser(const BuildInUriParser& Source) = delete;

		BuildInUriParser(BuildInUriParser&& Right) noexcept = delete;

		virtual ~BuildInUriParser();
	public:
		BuildInUriParser& operator=(const BuildInUriParser& Source) = delete;

		BuildInUriParser& operator=(BuildInUriParser&& Right) noexcept = delete;
	};
}
#endif
