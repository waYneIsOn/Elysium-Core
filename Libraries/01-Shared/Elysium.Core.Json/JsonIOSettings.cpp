#include "JsonIOSettings.hpp"

Elysium::Core::Json::JsonIOSettings::JsonIOSettings()
#ifdef UNICODE
	: _IndentSpace(L" "), _Indent(L"\t"), _NewLine(L"\r\n")
#else
	: _IndentSpace(" "), _Indent("\t"), _NewLine("\r\n")
#endif
{
}
Elysium::Core::Json::JsonIOSettings::JsonIOSettings(const String & IndentSpace, const String & Indent, const String & NewLine)
	: _IndentSpace(String(IndentSpace)), _Indent(String(Indent)), _NewLine(String(NewLine))
{
}
Elysium::Core::Json::JsonIOSettings::JsonIOSettings(const JsonIOSettings & Source)
	: _IndentSpace(Source._IndentSpace), _Indent(Source._Indent), _NewLine(Source._NewLine)
{
}
Elysium::Core::Json::JsonIOSettings::~JsonIOSettings()
{
}

Elysium::Core::Json::JsonIOSettings & Elysium::Core::Json::JsonIOSettings::operator=(const JsonIOSettings & Source)
{
	if (this != &Source)
	{
		_IndentSpace = Source._IndentSpace;
		_Indent = Source._Indent;
		_NewLine = Source._NewLine;
	}
	return *this;
}
