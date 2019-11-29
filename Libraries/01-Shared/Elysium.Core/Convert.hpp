/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_CONVERT
#define ELYSIUM_CORE_CONVERT

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef _STDINT
#include <stdint.h>
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API Convert final
		{
		public:
			~Convert();

			static String ToString(const int32_t Value, const int32_t FromBase);
			static String ToString(const float Value, const int32_t FromBase);
			static String ToString(const double Value, const int32_t FromBase);

			static int32_t ToInt32(const char16_t * Value, const int32_t FromBase);
			static int32_t ToInt32(const Elysium::Core::String& Value, const int32_t FromBase);
		private:
			Convert();
		};
	}
}
#endif
