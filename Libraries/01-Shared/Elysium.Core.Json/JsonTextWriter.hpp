/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONTEXTWRITER
#define ELYSIUM_CORE_JSON_JSONTEXTWRITER

#ifndef ELYSIUM_CORE_JSON_JSONWRITER
#include "JsonWriter.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_TEXTWRITER
#include "../Elysium.Core.IO/TextWriter.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_API JsonTextWriter final : public JsonWriter
			{
			public:
				JsonTextWriter(Elysium::Core::IO::TextWriter& Writer);
				JsonTextWriter(const JsonIOSettings& IOSettings, Elysium::Core::IO::TextWriter& Writer);
				~JsonTextWriter();
			protected:
				virtual void WriteString(const char16_t Value) override;
				virtual void WriteString(const String& Value) override;
			private:
				Elysium::Core::IO::TextWriter& _Writer;
			};
		}
	}
}
#endif
