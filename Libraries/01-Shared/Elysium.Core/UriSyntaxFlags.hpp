/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_URISYNTAXFLAGS
#define ELYSIUM_CORE_URISYNTAXFLAGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

namespace Elysium::Core
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class UriSyntaxFlags : uint32_t
#elif defined(__ANDROID__)
	enum class UriSyntaxFlags
#else
#error "undefined os"
#endif
	{
		None = 0x00,

		MustHaveAuthority = 0x1,
		OptionalAuthority = 0x2,
		MayHaveUserInfo = 0x4,
		MayHavePort = 0x8,
		MayHavePath = 0x10,
		MayHaveQuery = 0x20,
		MayHaveFragment = 0x40,

		AllowEmptyHost = 0x80,
		AllowUncHost = 0x100,
		AllowDnsHost = 0x200,
		AllowIPv4Host = 0x400,
		AllowIPv6Host = 0x800,
		AllowAnInternetHost = AllowDnsHost | AllowIPv4Host | AllowIPv6Host,
		AllowAnyOtherHost = 0x1000,

		FileLikeUri = 0x2000,
		MailToLikeUri = 0x4000,

		V1_UnknownUri = 0x10000,
		SimpleUserSyntax = 0x20000,
		BuiltInSyntax = 0x40000,
		ParserSchemeOnly = 0x80000,

		AllowDOSPath = 0x100000,
		PathIsRooted = 0x200000,
		ConvertPathSlashes = 0x400000,
		CompressPath = 0x800000,
		CanonicalizeAsFilePath = 0x1000000,
		UnEscapeDotsAndSlashes = 0x2000000,
		AllowIdn = 0x4000000,
		AllowIriParsing = 0x10000000,
	};

	inline UriSyntaxFlags operator|(UriSyntaxFlags lhs, UriSyntaxFlags rhs)
	{
		return static_cast<UriSyntaxFlags>(static_cast<int>(lhs) | static_cast<int>(rhs));
	}
	inline UriSyntaxFlags operator&(UriSyntaxFlags lhs, UriSyntaxFlags rhs)
	{
		return static_cast<UriSyntaxFlags>(static_cast<int>(lhs) & static_cast<int>(rhs));
	}
}
#endif
