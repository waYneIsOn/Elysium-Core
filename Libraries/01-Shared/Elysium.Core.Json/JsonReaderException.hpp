/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#define ELYSIUM_CORE_JSON_JSONREADEREXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_JSON_JSONEXCEPTION
#include "JsonException.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonReaderException final : public JsonException
	{
	public:
		JsonReaderException();

		JsonReaderException(Elysium::Core::Utf8String&& Message);

		virtual ~JsonReaderException();
	};
}
#endif
