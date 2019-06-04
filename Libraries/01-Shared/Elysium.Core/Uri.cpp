#include "Uri.hpp"
/*
#ifndef ELYSIUM_CORE_URIPARSER
#include "UriParser.hpp"
#endif

#ifndef ELYSIUM_CORE_URIPARSERTABLE
#include "UriParserTable.hpp"
#endif

#ifndef _ALGORITHM_
#include <algorithm>
#endif

Elysium::Core::Uri::Uri(const string& UriString)
	: _OriginalString(string(UriString.c_str())), _AbsoluteUri(_OriginalString)
{
	Parse();
}
Elysium::Core::Uri::~Uri()
{
}

const string_view & Elysium::Core::Uri::GetAbsoluteUri() const
{
	return _AbsoluteUri;
}
const string_view & Elysium::Core::Uri::GetSchema() const
{
	return _SchemeView;
}
const string_view & Elysium::Core::Uri::GetAuthority() const
{
	return _AuthorityView;
}
const string_view & Elysium::Core::Uri::GetUserInfo() const
{
	return _UserInfoView;
}
const string_view & Elysium::Core::Uri::GetHost() const
{
	return _HostView;
}
const int & Elysium::Core::Uri::GetPort() const
{
	return _Port;
}
const string_view & Elysium::Core::Uri::GetPathAndQuery() const
{
	return _PathAndQueryView;
}
const string_view & Elysium::Core::Uri::GetPath() const
{
	return _PathView;
}
const string_view & Elysium::Core::Uri::GetQuery() const
{
	return _QueryView;
}
const string_view & Elysium::Core::Uri::GetFragment() const
{
	return _FragmentView;
}

void Elysium::Core::Uri::Parse()
{
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
	*-/
}
*/