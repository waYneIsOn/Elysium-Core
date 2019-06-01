#include "UriParser.hpp"

#ifndef ELYSIUM_CORE_URIPARSERTABLE
#include "UriParserTable.hpp"
#endif

#ifndef _ALGORITHM_
#include <algorithm>
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../Elysium.Core/NotImplementedException.hpp"
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

Elysium::Core::UriParserTable Elysium::Core::UriParser::_ParserTable = Elysium::Core::UriParserTable();

Elysium::Core::UriParser::~UriParser()
{
}

Elysium::Core::UriParser::UriParser(std::string Scheme, int Port, UriSyntaxFlags RequiredComponents)
	: _Scheme(Scheme), _Port(Port), _RequiredComponents(RequiredComponents)
{
}

void Elysium::Core::UriParser::Register(UriParser * UriParser, std::string SchemeName, int DefaultPort)
{
	if (UriParser == nullptr)
	{
		//throw ArgumentNullException("UriParser");
	}

	// ToDo: use copy constructor to guarantee we have a new instanceof an UriParser?
	std::transform(SchemeName.begin(), SchemeName.end(), SchemeName.begin(), ::tolower);
	Elysium::Core::UriParser::_ParserTable.Map[SchemeName] = UriParser;
}

std::string_view Elysium::Core::UriParser::ParseComponent(UriComponents Component, std::string * const Source)
{
	switch (Component)
	{
	case Elysium::Core::UriComponents::Scheme:
	{
		size_t IndexOfSchemeDelimiterStart = Source->find(":");
		return std::string_view(&(Source->c_str()[0]), IndexOfSchemeDelimiterStart);
	}
	/*
	case Elysium::Core::UriComponents::UserInfo:
	{

	}
	case Elysium::Core::UriComponents::Host:
	{

	}
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
		size_t OriginalUriLength = Source->length();
		return std::string_view(&(Source->c_str()[0]), OriginalUriLength);
	}
	/*
	case Elysium::Core::UriComponents::HostAndPort:
	{

	}
	*/
	case Elysium::Core::UriComponents::StrongAuthority:
	{
		size_t OriginalUriLength = Source->length();

		// get the first "://" to determine where the scheme ends
		size_t IndexOfSchemeDelimiterStart = Source->find("://");
		size_t SchemeDelimiterLength = 3;

		// if we don't have the scheme delimiter start, just look up ":" as the scheme delimiter
		if (IndexOfSchemeDelimiterStart == string::npos)
		{
			IndexOfSchemeDelimiterStart = Source->find(":");
			SchemeDelimiterLength = 1;
		}
		const size_t IndexOfSchemeDelimiterEnd = IndexOfSchemeDelimiterStart + SchemeDelimiterLength;

		size_t RelativeIndexOfAuthorityDelimiterStart = Source->find("/", IndexOfSchemeDelimiterEnd);
		size_t RelativeIndexOfAuthorityDelimiterEnd = RelativeIndexOfAuthorityDelimiterStart + 1;
		if (RelativeIndexOfAuthorityDelimiterStart == string::npos)
		{
			RelativeIndexOfAuthorityDelimiterEnd = OriginalUriLength - IndexOfSchemeDelimiterEnd;
		}

		if (RelativeIndexOfAuthorityDelimiterStart != string::npos)
		{
			return std::string_view(&(Source->c_str()[IndexOfSchemeDelimiterEnd]), RelativeIndexOfAuthorityDelimiterEnd - IndexOfSchemeDelimiterEnd - 1);
		}
		else if (OriginalUriLength > IndexOfSchemeDelimiterEnd)
		{	// no slash the the end of the string so grab everything after the scheme delimiter
			return std::string_view(&(Source->c_str()[IndexOfSchemeDelimiterEnd]), OriginalUriLength - IndexOfSchemeDelimiterEnd);
		}
	}
	/*
	case Elysium::Core::UriComponents::SchemeAndServer:
	{

	}
	case Elysium::Core::UriComponents::HttpRequestUrl:
	{

	}
	case Elysium::Core::UriComponents::PathAndQuery:
	{

	}
	*/
	default:
		throw NotImplementedException((L"unknown component " + std::to_wstring((int)Component)).c_str());
	}
}
