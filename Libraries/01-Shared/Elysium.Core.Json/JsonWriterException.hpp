/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

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

		JsonWriterException(Elysium::Core::Utf8String&& Message);

		virtual ~JsonWriterException();
	};
}
#endif
