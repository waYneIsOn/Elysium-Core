/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONTEXTREADER
#define ELYSIUM_CORE_JSON_JSONTEXTREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_JSONREADER
#include "JsonReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_TEXTREADER
#include "../Elysium.Core.IO/TextReader.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonTextReader final : public JsonReader
	{
	public:
		JsonTextReader(Elysium::Core::IO::TextReader& Reader);
		JsonTextReader(const JsonIOSettings& IOSettings, Elysium::Core::IO::TextReader& Reader);
		~JsonTextReader();
	private:
		Elysium::Core::IO::TextReader& _Reader;

		virtual const int32_t PeekNextCharacterFromSource() override;
		virtual const int32_t ReadNextCharacterFromSource() override;
	};
}
#endif
