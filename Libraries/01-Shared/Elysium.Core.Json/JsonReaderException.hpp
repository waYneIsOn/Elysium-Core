/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONREADEREXCEPTION
#define ELYSIUM_CORE_JSON_JSONREADEREXCEPTION

#ifndef ELYSIUM_CORE_JSON_JSONEXCEPTION
#include "JsonException.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Json
		{
			class ELYSIUM_CORE_API JsonReaderException final : public JsonException
			{
			public:
				JsonReaderException();
				JsonReaderException(const String& Message);
				~JsonReaderException();
			};
		}
	}
}
#endif
