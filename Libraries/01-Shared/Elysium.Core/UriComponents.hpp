/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_URICOMPONENTS
#define ELYSIUM_CORE_URICOMPONENTS

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

namespace Elysium::Core
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class UriComponents : uint32_t
#elif defined(__ANDROID__)
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

	inline UriComponents operator|(UriComponents lhs, UriComponents rhs)
	{
		return static_cast<UriComponents>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}
	inline UriComponents operator&(UriComponents lhs, UriComponents rhs)
	{
		return static_cast<UriComponents>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}
}
#endif
