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
Elysium::Core::Collections::Template::Dictionary<Elysium::Core::String, Elysium::Core::UriParser> Elysium::Core::UriParser::_RegisteredParser =
	Elysium::Core::Collections::Template::Dictionary<Elysium::Core::String, Elysium::Core::UriParser>();
*/
Elysium::Core::UriParser::~UriParser()
{ }

const bool Elysium::Core::UriParser::IsKnownScheme(const Elysium::Core::String& SchemeName)
{
	return IsKnownScheme(Elysium::Core::StringView(SchemeName));
}

const bool Elysium::Core::UriParser::IsKnownScheme(const Elysium::Core::StringView& SchemeName)
{
	throw 1;
}

void Elysium::Core::UriParser::Register(const Elysium::Core::UriParser & UriParser, const Elysium::Core::String & SchemeName, const Elysium::Core::uint16_t DefaultPort)
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

Elysium::Core::StringView Elysium::Core::UriParser::ParseComponent(const Elysium::Core::UriComponents Component, const Elysium::Core::String & Source)
{
	// URI = scheme:[//authority]path[?query][#fragment]
	// authority = [userinfo@]host[:port]
	// scheme : //
	// userinfo @ host : port

	if (String::IsNullOrEmtpy(Source))
	{
		return StringView();
	}

	switch (Component)
	{
	case Elysium::Core::UriComponents::Scheme:
	{
		size_t IndexOfSchemeDelimiterEnd = Source.IndexOf(u8':');
		return StringView(Source, IndexOfSchemeDelimiterEnd);
	}
	/*
	case Elysium::Core::UriComponents::UserInfo:
	{

	}
	*/
	case Elysium::Core::UriComponents::Host:
	{
		// calculate the start index
		size_t OriginalUriLength = Source.GetLength();
		size_t IndexOfSchemeDelimiterEnd = Source.IndexOf(u8':');
		size_t IndexOfHostStart = IndexOfSchemeDelimiterEnd + 1;

		size_t IndexOfAuthorityDelimiterStart = Source.IndexOf(u8"//");
		size_t IndexOfPathDelimiterStart = Source.IndexOf(u8'/');
		if (IndexOfAuthorityDelimiterStart != static_cast<size_t>(-1))
		{
			IndexOfHostStart = IndexOfAuthorityDelimiterStart + 2;
			IndexOfPathDelimiterStart = Source.IndexOf(u8'/', IndexOfAuthorityDelimiterStart + 3);
			if (IndexOfPathDelimiterStart != static_cast<size_t>(-1))
			{
				IndexOfPathDelimiterStart += IndexOfAuthorityDelimiterStart + 3;
			}
		}

		size_t IndexOfHostDelimiterStart = Source.IndexOf(u8'@');
		if (IndexOfHostDelimiterStart != static_cast<size_t>(-1))
		{
			IndexOfHostStart = IndexOfHostDelimiterStart + 1;
		}

		// calculate the end index
		size_t IndexOfHostEnd = IndexOfPathDelimiterStart;
		if (IndexOfPathDelimiterStart == static_cast<size_t>(-1))
		{
			IndexOfHostEnd = OriginalUriLength;
		}

		size_t IndexOfPortDelimiter = Source.IndexOf(u8':', IndexOfHostStart + 1);
		if (IndexOfPortDelimiter != static_cast<size_t>(-1))
		{
			IndexOfHostEnd = IndexOfPortDelimiter + IndexOfHostStart + 1;
		}
		
		return StringView(Source, IndexOfHostStart, IndexOfHostEnd - IndexOfHostStart);
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
		return StringView(Source);
	}
	/*
	case Elysium::Core::UriComponents::HostAndPort:
	{

	}
	*/
	/*
	case Elysium::Core::UriComponents::StrongAuthority:
	{
		size_t OriginalUriLength = Source->GetLength();

		// get the first "://" to determine where the scheme ends
		size_t IndexOfSchemeDelimiterStart = Source->IndexOf(L"://");
		size_t SchemeDelimiterLength = 3;

		// if we don't have the scheme delimiter start, just look up ":" as the scheme delimiter
		if (IndexOfSchemeDelimiterStart == static_cast<size_t>(-1))
		{
			IndexOfSchemeDelimiterStart = Source->IndexOf(L':');
			SchemeDelimiterLength = 1;
		}
		const size_t IndexOfSchemeDelimiterEnd = IndexOfSchemeDelimiterStart + SchemeDelimiterLength;

		size_t RelativeIndexOfAuthorityDelimiterStart = Source->IndexOf(L'/', IndexOfSchemeDelimiterEnd);
		size_t RelativeIndexOfAuthorityDelimiterEnd = RelativeIndexOfAuthorityDelimiterStart + 1;
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
		size_t IndexOfAuthorityDelimiterStart = Source.IndexOf(u8"//");
		size_t IndexOfPathDelimiterStart = Source.IndexOf(u8'/');
		if (IndexOfAuthorityDelimiterStart != static_cast<size_t>(-1))
		{
			IndexOfPathDelimiterStart = Source.IndexOf(u8'/', IndexOfAuthorityDelimiterStart + 3);
			if (IndexOfPathDelimiterStart == static_cast<size_t>(-1))
			{	// Uri doesn't contain a path
				break;
			}
			else
			{
				IndexOfPathDelimiterStart += +IndexOfAuthorityDelimiterStart + 3;
			}
		}

		if (IndexOfPathDelimiterStart == static_cast<size_t>(-1))
		{	// Uri doesn't contain a path
			break;
		}

		size_t IndexOfFragmentDelimiterStart = Source.IndexOf(u8'#');
		if (IndexOfFragmentDelimiterStart == static_cast<size_t>(-1))
		{
			size_t OriginalUriLength = Source.GetLength();
			return StringView(Source, IndexOfPathDelimiterStart + 1, OriginalUriLength - IndexOfPathDelimiterStart - 1);
		}
		else
		{
			return StringView(Source, IndexOfPathDelimiterStart + 1, IndexOfFragmentDelimiterStart - IndexOfPathDelimiterStart - 1);
		}
	}
	default:
		// ToDo: throw specific exception
		throw 1;
	}
}

Elysium::Core::UriParser::UriParser(const Elysium::Core::String& Scheme, int Port, Elysium::Core::UriSyntaxFlags RequiredComponents)
	: _Scheme(Scheme), _Port(Port), _RequiredComponents(RequiredComponents)
{ }
