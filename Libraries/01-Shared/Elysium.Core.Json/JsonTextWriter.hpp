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
				~JsonTextWriter();

				virtual void WriteStartObject() override;
				virtual void WriteEndObject() override;

				virtual void WriteStartArray() override;
				virtual void WriteEndArray() override;

				virtual void WritePropertyName(const String& Name) override;

				virtual void WriteValue(const int& Value) override;
				virtual void WriteValue(const String& Value) override;

				virtual void WriteNull() override;

				virtual void WriteComment(const String& Comment) override;
			protected:
				virtual void WriteIndent() override;
				virtual void WriteValueDelimiter() override;
				virtual void WriteIndentSpace() override;
			private:
				Elysium::Core::IO::TextWriter& _Writer;
			};
		}
	}
}
#endif
