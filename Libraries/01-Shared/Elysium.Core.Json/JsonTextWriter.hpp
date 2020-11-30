/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONTEXTWRITER
#define ELYSIUM_CORE_JSON_JSONTEXTWRITER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_JSONWRITER
#include "JsonWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_TEXTWRITER
#include "../Elysium.Core.IO/TextWriter.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonTextWriter final : public JsonWriter
	{
	public:
		JsonTextWriter(Elysium::Core::IO::TextWriter& Writer);
		JsonTextWriter(const JsonIOSettings& IOSettings, Elysium::Core::IO::TextWriter& Writer);
		~JsonTextWriter();
	protected:
		virtual void WriteString(const char8_t Value) override;
		virtual void WriteString(const String& Value) override;
	private:
		Elysium::Core::IO::TextWriter& _Writer;
	};
}
#endif
