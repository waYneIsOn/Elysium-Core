/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONREADER
#define ELYSIUM_CORE_JSON_JSONREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_API
#include "API.hpp"
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

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_TEXT_STRINGBUILDER
#include "../Elysium.Core.Text/StringBuilder.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonReader
	{
	protected:
		JsonReader(const JsonIOSettings& IOSettings);
	public:
		virtual ~JsonReader();
	public:
		const JsonToken GetToken() const;

		const Elysium::Core::Utf8String& GetNodeValue() const;

		virtual bool Read();
		//void ReadContentAsBoolean();
		//void ReadContentAsString();

		//virtual void Skip();
	protected:
		virtual const int32_t PeekNextCharacterFromSource() = 0;
		virtual const int32_t ReadNextCharacterFromSource() = 0;

		virtual bool ReadProperty();

		virtual bool ReadValueNumeric(const int32_t FirstCharacter);
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
		Elysium::Core::Utf8String _CurrentNodeValue;

		Elysium::Core::Text::Utf8StringBuilder _PropertyBuffer;

		void EatIndent();
	};
}
#endif
