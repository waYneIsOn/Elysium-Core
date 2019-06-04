/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_URI
#define ELYSIUM_CORE_URI
/*
#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

#ifndef _XSTRING_
#include <string>
#include <string_view>
#endif

using std::string;
using std::string_view;

#pragma warning(disable : 4251)

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
		*-/
		class EXPORT Uri final
		{
		public:
			// constructors & destructors
			Uri(const string& UriString);
			~Uri();

			// fields
			static const string SchemeDelimiter;

			static const string UriSchemeFile;
			static const string UriSchemeFtp;
			static const string UriSchemeGopher;
			static const string UriSchemeHttp;
			static const string UriSchemeHttps;
			static const string UriSchemeIrc;
			static const string UriSchemeLdap;
			static const string UriSchemeMailto;
			static const string UriSchemeNetPipe;
			static const string UriSchemeNetTcp;
			static const string UriSchemeNews;
			static const string UriSchemeNntp;
			static const string UriSchemeSecureWebSocket;
			static const string UriSchemeTel;
			static const string UriSchemeTelNet;
			static const string UriSchemeUrn;
			static const string UriSchemeWebSocket;

			// properties - getter
			const string_view& GetAbsoluteUri() const;
			const string_view& GetSchema() const;
			const string_view& GetAuthority() const;
			const string_view& GetUserInfo() const;
			const string_view& GetHost() const;
			const int& GetPort() const;
			const string_view& GetPathAndQuery() const;
			const string_view& GetPath() const;
			const string_view& GetQuery() const;
			const string_view& GetFragment() const;

		protected:
			void Parse();
		private:
			// fields
			string _OriginalString;

			string_view _AbsoluteUri;
			string_view _SchemeView;
			string_view _AuthorityView;
			string_view _UserInfoView;
			string_view _HostView;
			int _Port = -1;
			string_view _PathAndQueryView;
			string_view _PathView;
			string_view _QueryView;
			string_view _FragmentView;
		};

		// define static Uri fields
		const string Elysium::Core::Uri::SchemeDelimiter("://");

		const string Elysium::Core::Uri::UriSchemeFile("file");
		const string Elysium::Core::Uri::UriSchemeFtp("ftp");
		const string Elysium::Core::Uri::UriSchemeGopher("gopher");
		const string Elysium::Core::Uri::UriSchemeHttp("http");
		const string Elysium::Core::Uri::UriSchemeHttps("https");
		const string Elysium::Core::Uri::UriSchemeIrc("irc");
		const string Elysium::Core::Uri::UriSchemeLdap("ldap");
		const string Elysium::Core::Uri::UriSchemeMailto("mailto");
		const string Elysium::Core::Uri::UriSchemeNetPipe("net.pipe");
		const string Elysium::Core::Uri::UriSchemeNetTcp("net.tcp");
		const string Elysium::Core::Uri::UriSchemeNews("news");
		const string Elysium::Core::Uri::UriSchemeNntp("nntp");
		const string Elysium::Core::Uri::UriSchemeSecureWebSocket("wss");
		const string Elysium::Core::Uri::UriSchemeTel("tel");
		const string Elysium::Core::Uri::UriSchemeTelNet("telnet");
		const string Elysium::Core::Uri::UriSchemeUrn("urn");
		const string Elysium::Core::Uri::UriSchemeWebSocket("ws");
	}
}
*/
#endif
