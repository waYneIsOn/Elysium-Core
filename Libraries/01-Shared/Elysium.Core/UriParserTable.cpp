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
			{ L"dummy", new BuildInUriParser(L"dummy", -1, UriParser::DummySyntaxFlags) },
			
			{ L"file", new BuildInUriParser(L"file", -1, UriParser::HttpSyntaxFlags) },
			{ L"ftp", new BuildInUriParser(L"ftp", 21, UriParser::HttpSyntaxFlags) },
			{ L"gopher", new BuildInUriParser(L"gopher", 70, UriParser::HttpSyntaxFlags) },
			{ L"http", new BuildInUriParser(L"http", 80, UriParser::HttpSyntaxFlags) },
			{ L"https", new BuildInUriParser(L"https", 443, UriParser::HttpSyntaxFlags) },
			{ L"irc", new BuildInUriParser(L"irc", 6667, UriParser::HttpSyntaxFlags) },
			{ L"ldap", new BuildInUriParser(L"ldap", 389, UriParser::HttpSyntaxFlags) },
			{ L"mailto", new BuildInUriParser(L"mailto", 25, UriParser::HttpSyntaxFlags) },
			{ L"net.pipe", new BuildInUriParser(L"net.pipe", -1, UriParser::HttpSyntaxFlags) },
			{ L"net.tcp", new BuildInUriParser(L"net.tcp", 808, UriParser::HttpSyntaxFlags) },
			{ L"news", new BuildInUriParser(L"news", -1, UriParser::HttpSyntaxFlags) },
			{ L"nntp", new BuildInUriParser(L"nntp", 119, UriParser::HttpSyntaxFlags) },
			{ L"wss", new BuildInUriParser(L"wss", 443, UriParser::HttpSyntaxFlags) },
			{ L"tel", new BuildInUriParser(L"tel", 992, UriParser::HttpSyntaxFlags) },
			{ L"telnet", new BuildInUriParser(L"telnet", 992, UriParser::HttpSyntaxFlags) },
			{ L"urn", new BuildInUriParser(L"urn", 23, UriParser::HttpSyntaxFlags) },
			{ L"ws", new BuildInUriParser(L"ws", 80, UriParser::HttpSyntaxFlags) },
			
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