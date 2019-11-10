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

			static int32_t ToInt32(ElysiumChar* Value, int32_t FromBase);
			static int32_t ToInt32(Elysium::Core::String& Value, int32_t FromBase);
		private:
			Convert();
		};
	}
}
#endif
