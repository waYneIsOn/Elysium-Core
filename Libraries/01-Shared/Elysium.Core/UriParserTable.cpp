#include "UriParserTable.hpp"
/*
#ifndef ELYSIUM_CORE_URICOMPONENTS
#include "UriComponents.hpp"
#endif

#ifndef ELYSIUM_CORE_BUILDINURIPARSER
#include "BuildInUriParser.hpp"
#endif

#ifndef _ALGORITHM_
#include <algorithm>
#endif

using Elysium::Core::BuildInUriParser;
using Elysium::Core::UriSyntaxFlags;

Elysium::Core::UriParserTable::UriParserTable()
	: Map(
		{
			{ "dummy", new BuildInUriParser("dummy", -1, UriParser::DummySyntaxFlags) },

			{ "file", new BuildInUriParser("file", -1, UriParser::HttpSyntaxFlags) },
			{ "ftp", new BuildInUriParser("ftp", 21, UriParser::HttpSyntaxFlags) },
			{ "gopher", new BuildInUriParser("gopher", 70, UriParser::HttpSyntaxFlags) },
			{ "http", new BuildInUriParser("http", 80, UriParser::HttpSyntaxFlags) },
			{ "https", new BuildInUriParser("https", 443, UriParser::HttpSyntaxFlags) },
			{ "irc", new BuildInUriParser("irc", 6667, UriParser::HttpSyntaxFlags) },
			{ "ldap", new BuildInUriParser("ldap", 389, UriParser::HttpSyntaxFlags) },
			{ "mailto", new BuildInUriParser("mailto", 25, UriParser::HttpSyntaxFlags) },
			{ "net.pipe", new BuildInUriParser("net.pipe", -1, UriParser::HttpSyntaxFlags) },
			{ "net.tcp", new BuildInUriParser("net.tcp", 808, UriParser::HttpSyntaxFlags) },
			{ "news", new BuildInUriParser("news", -1, UriParser::HttpSyntaxFlags) },
			{ "nntp", new BuildInUriParser("nntp", 119, UriParser::HttpSyntaxFlags) },
			{ "wss", new BuildInUriParser("wss", 443, UriParser::HttpSyntaxFlags) },
			{ "tel", new BuildInUriParser("tel", 992, UriParser::HttpSyntaxFlags) },
			{ "telnet", new BuildInUriParser("telnet", 992, UriParser::HttpSyntaxFlags) },
			{ "urn", new BuildInUriParser("urn", 23, UriParser::HttpSyntaxFlags) },
			{ "ws", new BuildInUriParser("ws", 80, UriParser::HttpSyntaxFlags) },
		})
{
}
Elysium::Core::UriParserTable::~UriParserTable()
{
	std::map<String, UriParser*>::iterator Iterator = Map.begin();
	while (Iterator != Map.end())
	{
		delete Iterator->second;
		Iterator++;
	}
	Map.clear();
}
*/