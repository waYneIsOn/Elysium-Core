/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_URICOMPONENTS
#define ELYSIUM_CORE_URICOMPONENTS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "System.hpp"
#endif

namespace Elysium::Core
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class UriComponents : Elysium::Core::uint32_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class UriComponents
#else
#error "undefined os"
#endif
	{
		Scheme = 0x01,
		UserInfo = 0x02,
		Host = 0x04,
		Port = 0x08,
		Path = 0x10,
		Query = 0x20,
		Fragment = 0x40,

		StrongPort = 0x80,
		NormalizedHost = 0x100,

		KeepDelimiter = 0x40000000,

		AbsoluteUri = Scheme | UserInfo | Host | Port | Path | Query | Fragment,
		HostAndPort = Host | StrongPort,
		StrongAuthority = UserInfo | Host | StrongPort,
		SchemeAndServer = Scheme | Host | Port,
		HttpRequestUrl = Scheme | Host | Port | Path | Query,
		PathAndQuery = Path | Query,
	};

	inline UriComponents operator|(const UriComponents Left, const UriComponents Right)
	{
		return static_cast<UriComponents>(static_cast<Elysium::Core::uint32_t>(Left) | static_cast<Elysium::Core::uint32_t>(Right));
	}
	inline UriComponents operator&(const UriComponents Left, const UriComponents Right)
	{
		return static_cast<UriComponents>(static_cast<Elysium::Core::uint32_t>(Left) & static_cast<Elysium::Core::uint32_t>(Right));
	}
}
#endif
