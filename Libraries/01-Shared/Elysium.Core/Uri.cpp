#include "Uri.hpp"

#ifndef ELYSIUM_CORE_URIPARSER
#include "UriParser.hpp"
#endif

#ifndef ELYSIUM_CORE_BUILDINURIPARSER
#include "BuildInUriParser.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

const Elysium::Core::Utf8String Elysium::Core::Uri::SchemeDelimiter(u8"://");

const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeFile(u8"file");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeFtp(u8"ftp");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeGopher(u8"gopher");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeHttp(u8"http");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeHttps(u8"https");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeIrc(u8"irc");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeLdap(u8"ldap");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeMailto(u8"mailto");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeNetPipe(u8"net.pipe");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeNetTcp(u8"net.tcp");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeNews(u8"news");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeNntp(u8"nntp");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeSecureWebSocket(u8"wss");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeTel(u8"tel");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeTelNet(u8"telnet");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeUrn(u8"urn");
const Elysium::Core::Utf8String Elysium::Core::Uri::UriSchemeWebSocket(u8"ws");

Elysium::Core::Uri::Uri(const Elysium::Core::Utf8String& UriString)
	: _OriginalString(UriString), _SchemeView(ParseScheme()), _Parser(GetParser())
{ }

Elysium::Core::Uri::Uri(const Uri BaseUri, const Elysium::Core::Utf8String & RelativeUri)
	: _OriginalString(CreateUri(BaseUri._OriginalString, RelativeUri)), _SchemeView(ParseScheme()), _Parser(GetParser())
{ }

Elysium::Core::Uri::Uri(Elysium::Core::Utf8String&& UriString)
	: _OriginalString(UriString), _SchemeView(ParseScheme()), _Parser(GetParser())
{ }

Elysium::Core::Uri::Uri(const Uri & Source)
	: _OriginalString(Source._OriginalString), _SchemeView(ParseScheme()), _Parser(GetParser())
{ }

Elysium::Core::Uri::Uri(Uri && Right) noexcept
	: _OriginalString(), _SchemeView(), _Parser(GetParser())
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Uri::~Uri()
{ }

Elysium::Core::Uri & Elysium::Core::Uri::operator=(const Uri & Source)
{
	if (this != &Source)
	{
		_OriginalString = Elysium::Core::Utf8String(Source._OriginalString);
		/*
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
		*/
	}
	return *this;
}

Elysium::Core::Uri & Elysium::Core::Uri::operator=(Uri && Right) noexcept
{
	if (this != &Right)
	{
		_OriginalString = Elysium::Core::Template::Functional::Move(Right._OriginalString);
		/*
		_AbsoluteUri = Elysium::Core::Template::Functional::Move(Right._AbsoluteUri);
		_SchemeView = Elysium::Core::Template::Functional::Move(Right._SchemeView);
		_AuthorityView = Elysium::Core::Template::Functional::Move(Right._AuthorityView);
		_UserInfoView = Elysium::Core::Template::Functional::Move(Right._UserInfoView);
		_HostView = Elysium::Core::Template::Functional::Move(Right._HostView);
		_Port = Elysium::Core::Template::Functional::Move(Right._Port);
		_PathAndQueryView = Elysium::Core::Template::Functional::Move(Right._PathAndQueryView);
		_PathView = Elysium::Core::Template::Functional::Move(Right._PathView);
		_QueryView = Elysium::Core::Template::Functional::Move(Right._QueryView);
		_FragmentView = Elysium::Core::Template::Functional::Move(Right._FragmentView);
		*/
	}
	return *this;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetAbsoluteUri() const
{
	return _AbsoluteUri;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetSchema() const
{
	return _SchemeView;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetAuthority() const
{
	return _AuthorityView;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetUserInfo() const
{
	return _UserInfoView;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetHost() const
{
	return _HostView;
}

const Elysium::Core::uint32_t& Elysium::Core::Uri::GetPort() const
{
	return _Port;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetPathAndQuery() const
{
	return _PathAndQueryView;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetPath() const
{
	return _PathView;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetQuery() const
{
	return _QueryView;
}

const Elysium::Core::Utf8StringView& Elysium::Core::Uri::GetFragment() const
{
	return _FragmentView;
}

Elysium::Core::Utf8StringView Elysium::Core::Uri::ParseScheme()
{


	return Elysium::Core::Utf8StringView();
}

Elysium::Core::UriParser& Elysium::Core::Uri::GetParser()
{
	if (UriParser::IsKnownScheme(_SchemeView))
	{
		throw 1;
	}
	else
	{
		throw 1;
	}
}

const Elysium::Core::Utf8String Elysium::Core::Uri::CreateUri(const Uri& BaseUri, const Elysium::Core::Utf8String& RelativeUri)
{	// ToDo: make this function work correctly in all cases! atm it just concatenates two strings!
	Elysium::Core::Text::StringBuilder Builder = Elysium::Core::Text::StringBuilder(BaseUri._OriginalString.GetLength() + RelativeUri.GetLength());
	Builder.Append(BaseUri._OriginalString);
	Builder.Append(RelativeUri);

	return Builder.ToString();
}
