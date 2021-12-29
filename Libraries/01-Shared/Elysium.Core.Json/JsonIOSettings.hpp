/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONIOSETTINGS
#define ELYSIUM_CORE_JSON_JSONIOSETTINGS

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonIOSettings final
	{
		friend class JsonWriter;
		friend class JsonReader;
	public:
		JsonIOSettings();

		JsonIOSettings(const Utf8String& IndentSpace, const Utf8String& Indent, const Utf8String& NewLine);

		JsonIOSettings(const JsonIOSettings& Source);

		JsonIOSettings(JsonIOSettings&& Right) = delete;

		~JsonIOSettings();

		JsonIOSettings& operator=(const JsonIOSettings& Source);
	private:
		Utf8String _IndentSpace;
		Utf8String _Indent;
		Utf8String _NewLine;
	};
}
#endif
