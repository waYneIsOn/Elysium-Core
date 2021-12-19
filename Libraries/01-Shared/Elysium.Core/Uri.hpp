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

		Uri(const Elysium::Core::String& UriString);

		Uri(const Uri BaseUri, const Elysium::Core::String& RelativeUri);

		Uri(Elysium::Core::String&& UriString);

		Uri(const Uri& Source);

		Uri(Uri&& Right) noexcept;

		~Uri();
	public:
		Uri& operator=(const Uri& Source);

		Uri& operator=(Uri&& Right) noexcept;
	public:
		static const Elysium::Core::String SchemeDelimiter;

		static const Elysium::Core::String UriSchemeFile;
		static const Elysium::Core::String UriSchemeFtp;
		static const Elysium::Core::String UriSchemeGopher;
		static const Elysium::Core::String UriSchemeHttp;
		static const Elysium::Core::String UriSchemeHttps;
		static const Elysium::Core::String UriSchemeIrc;
		static const Elysium::Core::String UriSchemeLdap;
		static const Elysium::Core::String UriSchemeMailto;
		static const Elysium::Core::String UriSchemeNetPipe;
		static const Elysium::Core::String UriSchemeNetTcp;
		static const Elysium::Core::String UriSchemeNews;
		static const Elysium::Core::String UriSchemeNntp;
		static const Elysium::Core::String UriSchemeSecureWebSocket;
		static const Elysium::Core::String UriSchemeTel;
		static const Elysium::Core::String UriSchemeTelNet;
		static const Elysium::Core::String UriSchemeUrn;
		static const Elysium::Core::String UriSchemeWebSocket;
	public:
		const Elysium::Core::Utf8StringView& GetAbsoluteUri() const;
		const Elysium::Core::Utf8StringView& GetSchema() const;
		const Elysium::Core::Utf8StringView& GetAuthority() const;
		const Elysium::Core::Utf8StringView& GetUserInfo() const;
		const Elysium::Core::Utf8StringView& GetHost() const;
		const Elysium::Core::uint32_t& GetPort() const;
		const Elysium::Core::Utf8StringView& GetPathAndQuery() const;
		const Elysium::Core::Utf8StringView& GetPath() const;
		const Elysium::Core::Utf8StringView& GetQuery() const;
		const Elysium::Core::Utf8StringView& GetFragment() const;
	private:
		Elysium::Core::String _OriginalString;
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

		Elysium::Core::Utf8StringView ParseScheme();
		Elysium::Core::UriParser& GetParser();

		const Elysium::Core::String CreateUri(const Uri& BaseUri, const Elysium::Core::String& RelativeUri);
	};
}
#endif
