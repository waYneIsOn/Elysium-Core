#include "UriParser.hpp"

#ifndef ELYSIUM_CORE_URIPARSERTABLE
#include "UriParserTable.hpp"
#endif

#ifndef _ALGORITHM_
#include <algorithm>
#endif

#ifndef _STRING_
#include <string>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "NotImplementedException.hpp"
#endif

Elysium::Core::UriSyntaxFlags Elysium::Core::UriParser::DummySyntaxFlags =
UriSyntaxFlags::MayHaveUserInfo |
UriSyntaxFlags::MayHavePort |
UriSyntaxFlags::MayHavePath |
UriSyntaxFlags::MayHaveQuery |
UriSyntaxFlags::MayHaveFragment;

Elysium::Core::UriSyntaxFlags Elysium::Core::UriParser::HttpSyntaxFlags =
UriSyntaxFlags::MustHaveAuthority |
UriSyntaxFlags::MayHaveUserInfo |
UriSyntaxFlags::MayHavePort |
UriSyntaxFlags::MayHavePath |
UriSyntaxFlags::MayHaveQuery |
UriSyntaxFlags::MayHaveFragment |
UriSyntaxFlags::AllowUncHost |
UriSyntaxFlags::AllowAnInternetHost |
UriSyntaxFlags::PathIsRooted |
UriSyntaxFlags::ConvertPathSlashes |
UriSyntaxFlags::CompressPath |
UriSyntaxFlags::CanonicalizeAsFilePath |
UriSyntaxFlags::None |
UriSyntaxFlags::AllowIdn |
UriSyntaxFlags::AllowIriParsing;

//Elysium::Core::UriParserTable Elysium::Core::UriParser::_ParserTable = Elysium::Core::UriParserTable();

Elysium::Core::UriParser::~UriParser()
{
}

Elysium::Core::UriParser::UriParser(const String& Scheme, int Port, UriSyntaxFlags RequiredComponents)
	: _Scheme(Scheme), _Port(Port), _RequiredComponents(RequiredComponents)
{
}

void Elysium::Core::UriParser::Register(UriParser & UriParser, const String & SchemeName, int DefaultPort)
{
	throw NotImplementedException();
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

void Elysium::Core::UriParser::ParseComponent(UriComponents Component, const String & Source, StringView & Output)
{
	// URI = scheme:[//authority]path[?query][#fragment]
	// authority = [userinfo@]host[:port]
	// scheme : //
	// userinfo @ host : port

	switch (Component)
	{
	case Elysium::Core::UriComponents::Scheme:
	{
		size_t IndexOfSchemeDelimiterEnd = Source.IndexOf(L':');
		Output = StringView(Source, IndexOfSchemeDelimiterEnd);
		break;
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
		size_t IndexOfSchemeDelimiterEnd = Source.IndexOf(u':');
		size_t IndexOfHostStart = IndexOfSchemeDelimiterEnd + 1;

		size_t IndexOfAuthorityDelimiterStart = Source.IndexOf(u"//");
		size_t IndexOfPathDelimiterStart = Source.IndexOf(u'/');
		if (IndexOfAuthorityDelimiterStart != static_cast<size_t>(-1))
		{
			IndexOfHostStart = IndexOfAuthorityDelimiterStart + 2;
			IndexOfPathDelimiterStart = Source.IndexOf(u'/', IndexOfAuthorityDelimiterStart + 3);
			if (IndexOfPathDelimiterStart != static_cast<size_t>(-1))
			{
				IndexOfPathDelimiterStart += IndexOfAuthorityDelimiterStart + 3;
			}
		}

		size_t IndexOfHostDelimiterStart = Source.IndexOf(u'@');
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

		size_t IndexOfPortDelimiter = Source.IndexOf(u':', IndexOfHostStart + 1);
		if (IndexOfPortDelimiter != static_cast<size_t>(-1))
		{
			IndexOfHostEnd = IndexOfPortDelimiter + IndexOfHostStart + 1;
		}
		
		Output = StringView(Source, IndexOfHostStart, IndexOfHostEnd - IndexOfHostStart);
		break;
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
		Output = StringView(Source);
		break;
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
		size_t IndexOfAuthorityDelimiterStart = Source.IndexOf(u"//");
		size_t IndexOfPathDelimiterStart = Source.IndexOf(u'/');
		if (IndexOfAuthorityDelimiterStart != static_cast<size_t>(-1))
		{
			IndexOfPathDelimiterStart = Source.IndexOf(u'/', IndexOfAuthorityDelimiterStart + 3);
			if (IndexOfPathDelimiterStart == std::wstring::npos)
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

		size_t IndexOfFragmentDelimiterStart = Source.IndexOf(u'#');
		if (IndexOfFragmentDelimiterStart == static_cast<size_t>(-1))
		{
			size_t OriginalUriLength = Source.GetLength();
			Output = StringView(Source, IndexOfPathDelimiterStart + 1, OriginalUriLength - IndexOfPathDelimiterStart - 1);
		}
		else
		{
			Output = StringView(Source, IndexOfPathDelimiterStart + 1, IndexOfFragmentDelimiterStart - IndexOfPathDelimiterStart - 1);
		}
		break;
	}
	default:
		// ToDo:
		//throw NotImplementedException((u"unknown component " + std::to_wstring((int)Component)).c_str());
		throw NotImplementedException(u"unknown component ");
	}
}
