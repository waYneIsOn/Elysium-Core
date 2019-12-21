/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONWRITEREXCEPTION
#define ELYSIUM_CORE_JSON_JSONWRITEREXCEPTION

#ifndef ELYSIUM_CORE_JSON_JSONEXCEPTION
#include "JsonException.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonWriterException final : public JsonException
	{
	public:
		JsonWriterException();
		JsonWriterException(const String& Message);
		~JsonWriterException();
	};
}
#endif
