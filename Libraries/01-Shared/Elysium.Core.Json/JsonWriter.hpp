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

				void WriteStartObject();
				void WriteEndObject();

				void WriteStartArray();
				void WriteEndArray();

				void WritePropertyName(const String& Name);

				void WriteValue(const bool& Value);
				void WriteValue(const int& Value);
				void WriteValue(const float& Value);
				void WriteValue(const double& Value);
				void WriteValue(const wchar_t* Value);
				void WriteValue(const String& Value);

				void WriteNull();
			protected:
				void WriteIndent();
				void WriteValueDelimiter();
				void WriteIndentSpace();

				virtual void WriteString(const char& Value) = 0;
				virtual void WriteString(const wchar_t& Value) = 0;
				virtual void WriteString(const String& Value) = 0;

				JsonWriter();
			private:
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
				enum class JsonWriterState : uint32_t
#elif defined(__ANDROID__)
				enum class JsonWriterState
#else
#error "undefined os"
#endif
				{
					Initialized = 0,

					StartedObject = 1,
					EndedObject = 2,

					StartedArray = 3,
					EndedArray = 4,

					PropertyName = 5,
					PropertyValue = 6,

					Finished = 7,
					Error = 8
				};

				JsonWriterState _State;
				uint16_t _Depth;

				static const JsonWriterState _StateLookupTable[9][9];

				void PrepareWritingValue();
				void ValidateAndSet(JsonWriter::JsonWriterState AspiredState);
				void WriteEscapedString(const String& Value);
			};
		}
	}
}
#endif
