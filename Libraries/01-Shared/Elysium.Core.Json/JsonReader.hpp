/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONREADER
#define ELYSIUM_CORE_JSON_JSONREADER

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONIOSETTINGS
#include "JsonIOSettings.hpp"
#endif

#ifndef ELYSIUM_CORE_JSON_JSONTOKEN
#include "JsonToken.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_API JsonReader
			{
			public:
				virtual ~JsonReader();

				const JsonToken GetToken() const;
				const String& GetNodeName() const;
				const String& GetNodeValue() const;

				virtual bool Read();
				//void ReadContentAsBoolean();
				//void ReadContentAsString();

				//virtual void Skip();
			protected:
				JsonReader(const JsonIOSettings& IOSettings);

				virtual const int32_t ReadNextCharacterFromSource() = 0;

				virtual bool ReadDocument();

				//virtual bool ReadValueName();

				virtual bool ReadValueNumeric(const int32_t FirstCharacter);
				virtual bool ReadValueString();
				virtual bool ReadValueBool(const int32_t FirstCharacter);
				virtual bool ReadValueNull(const int32_t FirstCharacter);
			private:
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
				enum class JsonReaderState : uint32_t
#elif defined(__ANDROID__)
				enum class JsonReaderState
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

					InBetweenValues = 7,
					
					Finished = 8,
					Error = 9
				};

				JsonReaderState _State;
				const JsonIOSettings _IOSettings;

				JsonToken _CurrentToken;
				String _CurrentNodeName;
				String _CurrentNodeValue;
			};
		}
	}
}
#endif
