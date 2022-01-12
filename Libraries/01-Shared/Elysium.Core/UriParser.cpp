#include "UriParser.hpp"

const Elysium::Core::UriSyntaxFlags Elysium::Core::UriParser::_DummySyntaxFlags =
Elysium::Core::UriSyntaxFlags::MayHaveUserInfo |
Elysium::Core::UriSyntaxFlags::MayHavePort |
Elysium::Core::UriSyntaxFlags::MayHavePath |
Elysium::Core::UriSyntaxFlags::MayHaveQuery |
Elysium::Core::UriSyntaxFlags::MayHaveFragment;

const Elysium::Core::UriSyntaxFlags Elysium::Core::UriParser::_HttpSyntaxFlags =
Elysium::Core::UriSyntaxFlags::MustHaveAuthority |
Elysium::Core::UriSyntaxFlags::MayHaveUserInfo |
Elysium::Core::UriSyntaxFlags::MayHavePort |
Elysium::Core::UriSyntaxFlags::MayHavePath |
Elysium::Core::UriSyntaxFlags::MayHaveQuery |
Elysium::Core::UriSyntaxFlags::MayHaveFragment |
Elysium::Core::UriSyntaxFlags::AllowUncHost |
Elysium::Core::UriSyntaxFlags::AllowAnInternetHost |
Elysium::Core::UriSyntaxFlags::PathIsRooted |
Elysium::Core::UriSyntaxFlags::ConvertPathSlashes |
Elysium::Core::UriSyntaxFlags::CompressPath |
Elysium::Core::UriSyntaxFlags::CanonicalizeAsFilePath |
Elysium::Core::UriSyntaxFlags::None |
Elysium::Core::UriSyntaxFlags::AllowIdn |
Elysium::Core::UriSyntaxFlags::AllowIriParsing;
/*
Elysium::Core::Collections::Template::Dictionary<Elysium::Core::Utf8String, Elysium::Core::UriParser> Elysium::Core::UriParser::_RegisteredParser =
	Elysium::Core::Collections::Template::Dictionary<Elysium::Core::Utf8String, Elysium::Core::UriParser>();
*/
Elysium::Core::UriParser::~UriParser()
{ }

const bool Elysium::Core::UriParser::IsKnownScheme(const Elysium::Core::Utf8String& SchemeName)
{
	return IsKnownScheme(Elysium::Core::Utf8StringView(&SchemeName[0]));
}

const bool Elysium::Core::UriParser::IsKnownScheme(const Elysium::Core::Utf8StringView& SchemeName)
{
	throw 1;
}

void Elysium::Core::UriParser::Register(const Elysium::Core::UriParser & UriParser, const Elysium::Core::Utf8String & SchemeName, const Elysium::Core::uint16_t DefaultPort)
{
	throw 1;
	/*
	if (UriParser == nullptr)
	{
		//throw ArgumentNullException("UriParser");
	}

	// ToDo: use copy constructor to guarantee we have a new instanceof an UriParser?
	std::transform(SchemeName.begin(), SchemeName.end(), SchemeName.begin(), ::tolower);
	Elysium::Core::UriParser::_ParserTable.Map[SchemeName] = UriParser;
	*/
}

Elysium::Core::Utf8StringView Elysium::Core::UriParser::ParseComponent(const Elysium::Core::UriComponents Component, const Elysium::Core::Utf8String & Source)
{
	// URI = scheme:[//authority]path[?query][#fragment]
	// authority = [userinfo@]host[:port]
	// scheme : //
	// userinfo @ host : port

	if (Elysium::Core::Utf8String::IsEmpty(Source))
	{
		return Utf8StringView();
	}

	switch (Component)
	{
	case Elysium::Core::UriComponents::Scheme:
	{
		Elysium::Core::size IndexOfSchemeDelimiterEnd = Source.IndexOf(u8':');
		return Utf8StringView(&Source[0], IndexOfSchemeDelimiterEnd);
	}
	/*
	case Elysium::Core::UriComponents::UserInfo:
	{

	}
	*/
	case Elysium::Core::UriComponents::Host:
	{
		// calculate the start index
		Elysium::Core::size OriginalUriLength = Source.GetLength();
		Elysium::Core::size IndexOfSchemeDelimiterEnd = Source.IndexOf(u8':');
		Elysium::Core::size IndexOfHostStart = IndexOfSchemeDelimiterEnd + 1;

		Elysium::Core::size IndexOfAuthorityDelimiterStart = Source.IndexOf(u8"//");
		Elysium::Core::size IndexOfPathDelimiterStart = Source.IndexOf(u8'/');
		if (IndexOfAuthorityDelimiterStart != static_cast<Elysium::Core::size>(-1))
		{
			IndexOfHostStart = IndexOfAuthorityDelimiterStart + 2;
			IndexOfPathDelimiterStart = Source.IndexOf(u8'/', IndexOfAuthorityDelimiterStart + 3);
			if (IndexOfPathDelimiterStart != static_cast<Elysium::Core::size>(-1))
			{
				IndexOfPathDelimiterStart += IndexOfAuthorityDelimiterStart + 3;
			}
		}

		Elysium::Core::size IndexOfHostDelimiterStart = Source.IndexOf(u8'@');
		if (IndexOfHostDelimiterStart != static_cast<Elysium::Core::size>(-1))
		{
			IndexOfHostStart = IndexOfHostDelimiterStart + 1;
		}

		// calculate the end index
		Elysium::Core::size IndexOfHostEnd = IndexOfPathDelimiterStart;
		if (IndexOfPathDelimiterStart == static_cast<Elysium::Core::size>(-1))
		{
			IndexOfHostEnd = OriginalUriLength;
		}

		Elysium::Core::size IndexOfPortDelimiter = Source.IndexOf(u8':', IndexOfHostStart + 1);
		if (IndexOfPortDelimiter != static_cast<Elysium::Core::size>(-1))
		{
			IndexOfHostEnd = IndexOfPortDelimiter + IndexOfHostStart + 1;
		}
		
		return Utf8StringView(&Source[IndexOfHostStart], IndexOfHostEnd - IndexOfHostStart);
	}
	/*
	case Elysium::Core::UriComponents::Port:
	{

	}
	case Elysium::Core::UriComponents::Path:
	{

	}
	case Elysium::Core::UriComponents::Query:
	{

	}
	case Elysium::Core::UriComponents::Fragment:
	{

	}
	case Elysium::Core::UriComponents::StrongPort:
	{

	}
	case Elysium::Core::UriComponents::NormalizedHost:
	{

	}
	case Elysium::Core::UriComponents::KeepDelimiter:
	{

	}
	*/
	case Elysium::Core::UriComponents::AbsoluteUri:
	{
		return Utf8StringView(&Source[0]);
	}
	/*
	case Elysium::Core::UriComponents::HostAndPort:
	{

	}
	*/
	/*
	case Elysium::Core::UriComponents::StrongAuthority:
	{
		Elysium::Core::size OriginalUriLength = Source->GetLength();

		// get the first "://" to determine where the scheme ends
		Elysium::Core::size IndexOfSchemeDelimiterStart = Source->IndexOf(L"://");
		Elysium::Core::size SchemeDelimiterLength = 3;

		// if we don't have the scheme delimiter start, just look up ":" as the scheme delimiter
		if (IndexOfSchemeDelimiterStart == static_cast<Elysium::Core::size>(-1))
		{
			IndexOfSchemeDelimiterStart = Source->IndexOf(L':');
			SchemeDelimiterLength = 1;
		}
		const Elysium::Core::size IndexOfSchemeDelimiterEnd = IndexOfSchemeDelimiterStart + SchemeDelimiterLength;

		Elysium::Core::size RelativeIndexOfAuthorityDelimiterStart = Source->IndexOf(L'/', IndexOfSchemeDelimiterEnd);
		Elysium::Core::size RelativeIndexOfAuthorityDelimiterEnd = RelativeIndexOfAuthorityDelimiterStart + 1;
		if (RelativeIndexOfAuthorityDelimiterStart == std::string::npos)
		{
			RelativeIndexOfAuthorityDelimiterEnd = OriginalUriLength - IndexOfSchemeDelimiterEnd;
		}

		if (RelativeIndexOfAuthorityDelimiterStart != std::string::npos)
		{
			*Output = StringView(&Source->operator[](IndexOfSchemeDelimiterEnd), RelativeIndexOfAuthorityDelimiterEnd - IndexOfSchemeDelimiterEnd - 1);
			break;
		}
		else if (OriginalUriLength > IndexOfSchemeDelimiterEnd)
		{	// no slash the the end of the string so grab everything after the scheme delimiter
			*Output = StringView(&Source->operator[](IndexOfSchemeDelimiterEnd), OriginalUriLength - IndexOfSchemeDelimiterEnd);
			break;
		}
	}
	*/
	/*
	case Elysium::Core::UriComponents::SchemeAndServer:
	{

	}
	case Elysium::Core::UriComponents::HttpRequestUrl:
	{

	}
	*/
	case Elysium::Core::UriComponents::PathAndQuery:
	{
		Elysium::Core::size IndexOfAuthorityDelimiterStart = Source.IndexOf(u8"//");
		Elysium::Core::size IndexOfPathDelimiterStart = Source.IndexOf(u8'/');
		if (IndexOfAuthorityDelimiterStart != static_cast<Elysium::Core::size>(-1))
		{
			IndexOfPathDelimiterStart = Source.IndexOf(u8'/', IndexOfAuthorityDelimiterStart + 3);
			if (IndexOfPathDelimiterStart == static_cast<Elysium::Core::size>(-1))
			{	// Uri doesn't contain a path
				return Utf8StringView();
			}
			else
			{
				IndexOfPathDelimiterStart += +IndexOfAuthorityDelimiterStart + 3;
			}
		}

		if (IndexOfPathDelimiterStart == static_cast<Elysium::Core::size>(-1))
		{	// Uri doesn't contain a path
			return Utf8StringView();
		}

		Elysium::Core::size IndexOfFragmentDelimiterStart = Source.IndexOf(u8'#');
		if (IndexOfFragmentDelimiterStart == static_cast<Elysium::Core::size>(-1))
		{
			Elysium::Core::size OriginalUriLength = Source.GetLength();
			return Utf8StringView(&Source[IndexOfPathDelimiterStart + 1], OriginalUriLength - IndexOfPathDelimiterStart - 1);
		}
		else
		{
			return Utf8StringView(&Source[IndexOfPathDelimiterStart + 1], IndexOfFragmentDelimiterStart - IndexOfPathDelimiterStart - 1);
		}
	}
	default:
		// ToDo: throw specific exception
		throw 1;
	}
}

Elysium::Core::UriParser::UriParser(const Elysium::Core::Utf8String& Scheme, int Port, Elysium::Core::UriSyntaxFlags RequiredComponents)
	: _Scheme(Scheme), _Port(Port), _RequiredComponents(RequiredComponents)
{ }
