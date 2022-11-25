/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_URI
#define ELYSIUM_CORE_URI

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_URIKIND
#include "UriKind.hpp"
#endif

#ifndef ELYSIUM_CORE_URIPARSER
#include "UriParser.hpp"
#endif

namespace Elysium::Core
{
	/*
	[scheme:]scheme-specific-part[#fragment]
	mailto:john.doe@example.com
	news:comp.infosystems.www.servers.unix
	tel:+1-816-555-1212

	[scheme:][//authority][/path][?query][#fragment]
	[user_info@]host[:port]

	https://tools.ietf.org/html/rfc3986
	scheme ":" "hierarchical part" [ "?" query ] [ "#" fragment ]
	*/
	class ELYSIUM_CORE_API Uri final
	{
	public:
		Uri() = delete;

		Uri(const Elysium::Core::Utf8String& UriString);

		Uri(const Uri BaseUri, const Elysium::Core::Utf8String& RelativeUri);

		Uri(Elysium::Core::Utf8String&& UriString);

		Uri(const Uri& Source);

		Uri(Uri&& Right) noexcept;

		~Uri();
	public:
		Uri& operator=(const Uri& Source);

		Uri& operator=(Uri&& Right) noexcept;
	public:
		inline static const Elysium::Core::Utf8String SchemeDelimiter = u8"://";

		inline static const Elysium::Core::Utf8String UriSchemeFile = u8"file";

		inline static const Elysium::Core::Utf8String UriSchemeFtp = u8"ftp";

		inline static const Elysium::Core::Utf8String UriSchemeGopher = u8"gopher";

		inline static const Elysium::Core::Utf8String UriSchemeHttp = u8"http";

		inline static const Elysium::Core::Utf8String UriSchemeHttps = u8"https";

		inline static const Elysium::Core::Utf8String UriSchemeIrc = u8"irc";

		inline static const Elysium::Core::Utf8String UriSchemeLdap = u8"ldap";

		inline static const Elysium::Core::Utf8String UriSchemeMailto = u8"mailto";

		inline static const Elysium::Core::Utf8String UriSchemeNetPipe = u8"net.pipe";

		inline static const Elysium::Core::Utf8String UriSchemeNetTcp = u8"net.tcp";

		inline static const Elysium::Core::Utf8String UriSchemeNews = u8"news";

		inline static const Elysium::Core::Utf8String UriSchemeNntp = u8"nntp";

		inline static const Elysium::Core::Utf8String UriSchemeSecureWebSocket = u8"wss";

		inline static const Elysium::Core::Utf8String UriSchemeTel = u8"tel";

		inline static const Elysium::Core::Utf8String UriSchemeTelNet = u8"telnet";

		inline static const Elysium::Core::Utf8String UriSchemeUrn = u8"urn";

		inline static const Elysium::Core::Utf8String UriSchemeWebSocket = u8"ws";
	public:
		const Elysium::Core::Utf8StringView& GetAbsoluteUri() const;

		const Elysium::Core::Utf8StringView& GetSchema() const;

		const Elysium::Core::Utf8StringView& GetAuthority() const;

		const Elysium::Core::Utf8StringView& GetUserInfo() const;

		const Elysium::Core::Utf8StringView& GetHost() const;

		const Elysium::Core::uint32_t GetPort() const;

		const Elysium::Core::Utf8StringView& GetPathAndQuery() const;

		const Elysium::Core::Utf8StringView& GetPath() const;

		const Elysium::Core::Utf8StringView& GetQuery() const;

		const Elysium::Core::Utf8StringView& GetFragment() const;
	private:
		Elysium::Core::Utf8StringView ParseScheme();

		Elysium::Core::UriParser& GetParser();

		const Elysium::Core::Utf8String CreateUri(const Uri& BaseUri, const Elysium::Core::Utf8String& RelativeUri);
	private:
		Elysium::Core::Utf8String _OriginalString;
		Elysium::Core::Utf8StringView _SchemeView;
		Elysium::Core::UriParser& _Parser;

		Elysium::Core::Utf8StringView _AbsoluteUri;
		Elysium::Core::Utf8StringView _AuthorityView;
		Elysium::Core::Utf8StringView _UserInfoView;
		Elysium::Core::Utf8StringView _HostView;
		Elysium::Core::uint32_t _Port;
		Elysium::Core::Utf8StringView _PathAndQueryView;
		Elysium::Core::Utf8StringView _PathView;
		Elysium::Core::Utf8StringView _QueryView;
		Elysium::Core::Utf8StringView _FragmentView;
	};
}
#endif
