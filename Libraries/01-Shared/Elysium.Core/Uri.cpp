#include "Uri.hpp"

#ifndef ELYSIUM_CORE_URIPARSER
#include "UriParser.hpp"
#endif

#ifndef ELYSIUM_CORE_URIPARSERTABLE
#include "UriParserTable.hpp"
#endif

#ifndef _ALGORITHM_
#include <algorithm>
#endif

#ifndef ELYSIUM_CORE_BUILDINURIPARSER
#include "BuildInUriParser.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

const Elysium::Core::String Elysium::Core::Uri::SchemeDelimiter(u8"://");

const Elysium::Core::String Elysium::Core::Uri::UriSchemeFile(u8"file");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeFtp(u8"ftp");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeGopher(u8"gopher");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeHttp(u8"http");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeHttps(u8"https");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeIrc(u8"irc");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeLdap(u8"ldap");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeMailto(u8"mailto");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeNetPipe(u8"net.pipe");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeNetTcp(u8"net.tcp");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeNews(u8"news");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeNntp(u8"nntp");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeSecureWebSocket(u8"wss");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeTel(u8"tel");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeTelNet(u8"telnet");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeUrn(u8"urn");
const Elysium::Core::String Elysium::Core::Uri::UriSchemeWebSocket(u8"ws");

Elysium::Core::Uri::Uri(const String& UriString)
	: _OriginalString(String(UriString)), _AbsoluteUri(_OriginalString), _Port(-1)
{
	Parse();
}
Elysium::Core::Uri::Uri(const Uri & BaseUri, const String & RelativeUri)
	: _OriginalString(CreateUri(BaseUri._OriginalString, RelativeUri, true)), _AbsoluteUri(_OriginalString), _Port(-1)
{
	Parse();
}
Elysium::Core::Uri::Uri(const Uri & Source)
	: _OriginalString(String(Source._OriginalString)), _AbsoluteUri(_OriginalString), _Port(Source._Port)
{
	Parse();
}
Elysium::Core::Uri::Uri(Uri && Right) noexcept
	: _Port(-1)
{
	*this = std::move(Right);
}
Elysium::Core::Uri::~Uri()
{ }

Elysium::Core::Uri & Elysium::Core::Uri::operator=(const Uri & Source)
{
	if (this != &Source)
	{
		_OriginalString = String(Source._OriginalString);
		_AbsoluteUri = StringView(Source._AbsoluteUri);
		_SchemeView = StringView(Source._SchemeView);
		_AuthorityView = StringView(Source._AuthorityView);
		_UserInfoView = StringView(Source._UserInfoView);
		_HostView = StringView(Source._HostView);
		_Port = int32_t(Source._Port);
		_PathAndQueryView = StringView(Source._PathAndQueryView);
		_PathView = StringView(Source._PathView);
		_QueryView = StringView(Source._QueryView);
		_FragmentView = StringView(Source._FragmentView);
	}
	return *this;
}
Elysium::Core::Uri & Elysium::Core::Uri::operator=(Uri && Right) noexcept
{
	if (this != &Right)
	{
		_OriginalString = std::move(Right._OriginalString);
		_AbsoluteUri = std::move(Right._AbsoluteUri);
		_SchemeView = std::move(Right._SchemeView);
		_AuthorityView = std::move(Right._AuthorityView);
		_UserInfoView = std::move(Right._UserInfoView);
		_HostView = std::move(Right._HostView);
		_Port = Right._Port;
		_PathAndQueryView = std::move(Right._PathAndQueryView);
		_PathView = std::move(Right._PathView);
		_QueryView = std::move(Right._QueryView);
		_FragmentView = std::move(Right._FragmentView);
	}
	return *this;
}

const Elysium::Core::StringView & Elysium::Core::Uri::GetAbsoluteUri() const
{
	return _AbsoluteUri;
}
const Elysium::Core::StringView & Elysium::Core::Uri::GetSchema() const
{
	return _SchemeView;
}
const Elysium::Core::StringView & Elysium::Core::Uri::GetAuthority() const
{
	return _AuthorityView;
}
const Elysium::Core::StringView & Elysium::Core::Uri::GetUserInfo() const
{
	return _UserInfoView;
}
const Elysium::Core::StringView & Elysium::Core::Uri::GetHost() const
{
	return _HostView;
}
const int32_t & Elysium::Core::Uri::GetPort() const
{
	return _Port;
}
const Elysium::Core::StringView & Elysium::Core::Uri::GetPathAndQuery() const
{
	return _PathAndQueryView;
}
const Elysium::Core::StringView & Elysium::Core::Uri::GetPath() const
{
	return _PathView;
}
const Elysium::Core::StringView & Elysium::Core::Uri::GetQuery() const
{
	return _QueryView;
}
const Elysium::Core::StringView & Elysium::Core::Uri::GetFragment() const
{
	return _FragmentView;
}

void Elysium::Core::Uri::Parse()
{
	// ToDo: implement this correctly using a std::map where the according parsers are stored
	// for now just use the BuildInUriParser
	BuildInUriParser Parser = BuildInUriParser(u8"dummy", -1, UriParser::DummySyntaxFlags);
	Parser.ParseComponent(UriComponents::Scheme, _OriginalString, _SchemeView);
	Parser.ParseComponent(UriComponents::Host, _OriginalString, _HostView);
	Parser.ParseComponent(UriComponents::PathAndQuery, _OriginalString, _PathAndQueryView);

	/*
	// grab the dummy parser to parse the scheme
	UriParser* AccordingUriParser = Elysium::Core::UriParser::_ParserTable.Map["dummy"];
	_SchemeView = AccordingUriParser->ParseComponent(UriComponents::Scheme, &_OriginalString);

	// now that we have the scheme use it to find the parser that actually should be used
	AccordingUriParser = Elysium::Core::UriParser::_ParserTable.Map[(std::string)_SchemeView];

	if (AccordingUriParser == nullptr)
	{	// we do have an error
		// ToDo ... use a "default" parser?
	}
	else
	{	// parse away
		_AbsoluteUri = AccordingUriParser->ParseComponent(UriComponents::AbsoluteUri, &_OriginalString);
		_AuthorityView = AccordingUriParser->ParseComponent(UriComponents::StrongAuthority, &_OriginalString);
		/*
		_UserInfoView = AccordingUriParser->ParseComponent(UriComponents::UserInfo, &_OriginalString);
		_HostView = AccordingUriParser->ParseComponent(UriComponents::Host, &_OriginalString);
		//_Port = AccordingUriParser->ParseComponent(UriComponents::Port, &_OriginalString);
		_PathAndQueryView = AccordingUriParser->ParseComponent(UriComponents::PathAndQuery, &_OriginalString);
		_PathView = AccordingUriParser->ParseComponent(UriComponents::Path, &_OriginalString);
		_QueryView = AccordingUriParser->ParseComponent(UriComponents::Query, &_OriginalString);
		_FragmentView = AccordingUriParser->ParseComponent(UriComponents::Fragment, &_OriginalString);
		*-/
	}






	/*
	// ToDo:
	// write specific parser for specific uris!
	// "tel:+1-816-555-1212" should probably return the number as path, not as authority
	// since I don't need to parse such uris at the moment it's ok for now though

	size_t OriginalUriLength = _OriginalString.length();

	// find the next slash since that's the end of the authority part
	size_t RelativeIndexOfAuthorityDelimiterStart = _OriginalString.find("/", IndexOfSchemeDelimiterEnd);
	size_t RelativeIndexOfAuthorityDelimiterEnd = RelativeIndexOfAuthorityDelimiterStart + 1;
	if (RelativeIndexOfAuthorityDelimiterStart == string::npos)
	{
		RelativeIndexOfAuthorityDelimiterEnd = OriginalUriLength - IndexOfSchemeDelimiterEnd;
	}

	// find "?" as it is the start of the query
	const size_t RelativeIndexOfPathEnd = _OriginalString.find("?", RelativeIndexOfAuthorityDelimiterEnd);
	/*
	if (RelativeIndexOfPathEnd == string::npos)
	{

	}
	*-/

	// find "#" as the start of the fragment
	size_t RelativeIndexOfFragmentStart = _OriginalString.find("#", RelativeIndexOfAuthorityDelimiterEnd);

	// look further into the authority part
	size_t RelativeIndexOfUserInfoStart = string::npos;
	size_t RelativeIndexOfUserInfoEnd = string::npos;
	size_t RelativeIndexOfHostStart = string::npos;
	size_t RelativeIndexOfHostEnd = string::npos;
	size_t RelativeIndexOfPortStart = string::npos;
	size_t RelativeIndexOfPortEnd = string::npos;

	// get "@" as the end of userinfo
	size_t RelativeIndexOfHostDelimiterStart = _OriginalString.find("@", IndexOfSchemeDelimiterStart);

	// get ":" as the end of host
	size_t RelativeIndexOfPortDelimiterStart = _OriginalString.find(":", IndexOfSchemeDelimiterStart);

	// get the scheme
	if (IndexOfSchemeDelimiterStart != string::npos)
	{
		_SchemeView = string_view(&(_OriginalString.c_str()[0]), IndexOfSchemeDelimiterStart);
	}

	// get the authority
	if (RelativeIndexOfAuthorityDelimiterStart != string::npos)
	{
		_AuthorityView = string_view(&(_OriginalString.c_str()[IndexOfSchemeDelimiterEnd]), RelativeIndexOfAuthorityDelimiterEnd - IndexOfSchemeDelimiterEnd - 1);
	}
	else if (OriginalUriLength > IndexOfSchemeDelimiterEnd)
	{	// no slash the the end of the string so grab everything after the scheme delimiter
		_AuthorityView = string_view(&(_OriginalString.c_str()[IndexOfSchemeDelimiterEnd]), OriginalUriLength - IndexOfSchemeDelimiterEnd);
	}

	// get the userinfo
	if (RelativeIndexOfHostDelimiterStart != string::npos)
	{
		_UserInfoView = string_view(&(_OriginalString.c_str()[IndexOfSchemeDelimiterEnd]), RelativeIndexOfHostDelimiterStart - IndexOfSchemeDelimiterEnd);
	}

	// get the host
	if (RelativeIndexOfHostDelimiterStart != string::npos)
	{
		if (RelativeIndexOfPathEnd != string::npos)
		{
			_HostView = string_view(&(_OriginalString.c_str()[RelativeIndexOfHostDelimiterStart + 1]),
				RelativeIndexOfAuthorityDelimiterEnd);
		}
		else if (RelativeIndexOfFragmentStart != string::npos)
		{
			_HostView = string_view(&(_OriginalString.c_str()[RelativeIndexOfHostDelimiterStart + 1]), RelativeIndexOfFragmentStart - RelativeIndexOfAuthorityDelimiterEnd);
		}
		else
		{
			//_HostView = string_view(&(_OriginalString.c_str()[RelativeIndexOfHostDelimiterStart + 1]));
		}
	}
	else if (RelativeIndexOfPortDelimiterStart != string::npos)
	{
		_HostView = string_view(&(_OriginalString.c_str()[IndexOfSchemeDelimiterEnd]), RelativeIndexOfAuthorityDelimiterEnd - IndexOfSchemeDelimiterEnd - IndexOfSchemeDelimiterStart);
	}
	else
	{
		//_HostView = string_view(&(_OriginalString.c_str()[IndexOfSchemeDelimiterEnd]), RelativeIndexOfAuthorityDelimiterEnd - IndexOfSchemeDelimiterEnd);
	}

	// get the path and query
	if (RelativeIndexOfAuthorityDelimiterStart != string::npos)
	{
		if (RelativeIndexOfFragmentStart != string::npos)
		{
			_PathAndQueryView = string_view(&(_OriginalString.c_str()[RelativeIndexOfAuthorityDelimiterEnd]), RelativeIndexOfFragmentStart - RelativeIndexOfAuthorityDelimiterEnd);
		}
		else
		{
			_PathAndQueryView = string_view(&(_OriginalString.c_str()[RelativeIndexOfAuthorityDelimiterEnd]));
		}

		if (RelativeIndexOfPathEnd != string::npos)
		{
			_PathView = string_view(&(_OriginalString.c_str()[RelativeIndexOfAuthorityDelimiterEnd]), RelativeIndexOfPathEnd - RelativeIndexOfAuthorityDelimiterEnd);
			if (RelativeIndexOfFragmentStart != string::npos)
			{
				_QueryView = string_view(&(_OriginalString.c_str()[RelativeIndexOfPathEnd + 1]), RelativeIndexOfFragmentStart - RelativeIndexOfPathEnd - 1);
			}
			else
			{
				_QueryView = string_view(&(_OriginalString.c_str()[RelativeIndexOfPathEnd + 1]));
			}
		}
		else if(RelativeIndexOfFragmentStart != string::npos)
		{
			_PathView = string_view(&(_OriginalString.c_str()[RelativeIndexOfAuthorityDelimiterEnd]), RelativeIndexOfFragmentStart - RelativeIndexOfAuthorityDelimiterEnd);
		}
		else
		{
			_PathView = string_view(&(_OriginalString.c_str()[RelativeIndexOfAuthorityDelimiterEnd]));
		}
	}

	// get the fragment
	if (RelativeIndexOfFragmentStart != string::npos)
	{
		_FragmentView = string_view(&(_OriginalString.c_str()[RelativeIndexOfFragmentStart + 1]));
	}
	*/
}

const Elysium::Core::String Elysium::Core::Uri::CreateUri(const Uri & BaseUri, const String & RelativeUri, bool DontEscape)
{	// ToDo: make this function work correctly in all cases! atm it just concatenates two strings!
	Elysium::Core::Text::StringBuilder Builder = Elysium::Core::Text::StringBuilder(BaseUri._OriginalString.GetLength() + RelativeUri.GetLength());
	Builder.Append(BaseUri._OriginalString);
	Builder.Append(RelativeUri);

	return Builder.ToString();
}
