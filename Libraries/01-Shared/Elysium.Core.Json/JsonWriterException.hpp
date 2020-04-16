/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONWRITEREXCEPTION
#define ELYSIUM_CORE_JSON_JSONWRITEREXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_JSONEXCEPTION
#include "JsonException.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonWriterException final : public JsonException
	{
	public:
		JsonWriterException();
		JsonWriterException(String&& Message);
		virtual ~JsonWriterException();
	};
}
#endif
