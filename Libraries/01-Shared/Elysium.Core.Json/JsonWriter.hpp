/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONWRITER
#define ELYSIUM_CORE_JSON_JSONWRITER

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../Elysium.Core.IO/Stream.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_API JsonWriter
			{
			public:
				virtual ~JsonWriter() {}

				virtual void WriteStartObject();
				virtual void WriteEndObject();

				virtual void WriteStartArray();
				virtual void WriteEndArray();

				virtual void WritePropertyName(const String& Name);

				virtual void WriteValue(const int& Value);
				virtual void WriteValue(const String& Value);

				virtual void WriteNull();

				virtual void WriteComment(const String& Comment);
			protected:
				virtual void WriteIndent();
				virtual void WriteValueDelimiter();
				virtual void WriteIndentSpace();
			protected:
				JsonWriter();
			};
		}
	}
}
#endif
