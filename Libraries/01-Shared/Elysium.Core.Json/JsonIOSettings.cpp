#include "JsonIOSettings.hpp"

Elysium::Core::Json::JsonIOSettings::JsonIOSettings()
	: _IndentSpace(u8" "), _Indent(u8"\t"), _NewLine(u8"\r\n")
{
}
Elysium::Core::Json::JsonIOSettings::JsonIOSettings(const Utf8String& IndentSpace, const Utf8String& Indent, const Utf8String& NewLine)
	: _IndentSpace(IndentSpace), _Indent(Indent), _NewLine(NewLine)
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
