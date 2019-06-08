/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_URI
#define ELYSIUM_CORE_URI

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif

namespace Elysium
{
	namespace Core
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
			// constructors & destructors
			Uri(const String& UriString);
			~Uri();

			// fields
			static const String SchemeDelimiter;

			static const String UriSchemeFile;
			static const String UriSchemeFtp;
			static const String UriSchemeGopher;
			static const String UriSchemeHttp;
			static const String UriSchemeHttps;
			static const String UriSchemeIrc;
			static const String UriSchemeLdap;
			static const String UriSchemeMailto;
			static const String UriSchemeNetPipe;
			static const String UriSchemeNetTcp;
			static const String UriSchemeNews;
			static const String UriSchemeNntp;
			static const String UriSchemeSecureWebSocket;
			static const String UriSchemeTel;
			static const String UriSchemeTelNet;
			static const String UriSchemeUrn;
			static const String UriSchemeWebSocket;

			// properties - getter
			const StringView& GetAbsoluteUri() const;
			const StringView& GetSchema() const;
			const StringView& GetAuthority() const;
			const StringView& GetUserInfo() const;
			const StringView& GetHost() const;
			const int& GetPort() const;
			const StringView& GetPathAndQuery() const;
			const StringView& GetPath() const;
			const StringView& GetQuery() const;
			const StringView& GetFragment() const;

		protected:
			void Parse();
		private:
			// fields
			String _OriginalString;

			StringView _AbsoluteUri;
			StringView _SchemeView;
			StringView _AuthorityView;
			StringView _UserInfoView;
			StringView _HostView;
			int _Port = -1;
			StringView _PathAndQueryView;
			StringView _PathView;
			StringView _QueryView;
			StringView _FragmentView;
		};

		// define static Uri fields
		const String Elysium::Core::Uri::SchemeDelimiter(L"://");

		const String Elysium::Core::Uri::UriSchemeFile(L"file");
		const String Elysium::Core::Uri::UriSchemeFtp(L"ftp");
		const String Elysium::Core::Uri::UriSchemeGopher(L"gopher");
		const String Elysium::Core::Uri::UriSchemeHttp(L"http");
		const String Elysium::Core::Uri::UriSchemeHttps(L"https");
		const String Elysium::Core::Uri::UriSchemeIrc(L"irc");
		const String Elysium::Core::Uri::UriSchemeLdap(L"ldap");
		const String Elysium::Core::Uri::UriSchemeMailto(L"mailto");
		const String Elysium::Core::Uri::UriSchemeNetPipe(L"net.pipe");
		const String Elysium::Core::Uri::UriSchemeNetTcp(L"net.tcp");
		const String Elysium::Core::Uri::UriSchemeNews(L"news");
		const String Elysium::Core::Uri::UriSchemeNntp(L"nntp");
		const String Elysium::Core::Uri::UriSchemeSecureWebSocket(L"wss");
		const String Elysium::Core::Uri::UriSchemeTel(L"tel");
		const String Elysium::Core::Uri::UriSchemeTelNet(L"telnet");
		const String Elysium::Core::Uri::UriSchemeUrn(L"urn");
		const String Elysium::Core::Uri::UriSchemeWebSocket(L"ws");
	}
}
#endif
