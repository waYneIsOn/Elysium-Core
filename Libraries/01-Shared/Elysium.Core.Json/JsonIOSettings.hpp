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
		JsonIOSettings(const String& IndentSpace, const String& Indent, const String& NewLine);
		JsonIOSettings(const JsonIOSettings& Source);
		JsonIOSettings(JsonIOSettings&& Right) = delete;
		~JsonIOSettings();

		JsonIOSettings& operator=(const JsonIOSettings& Source);
	private:
		String _IndentSpace;
		String _Indent;
		String _NewLine;
	};
}
#endif
