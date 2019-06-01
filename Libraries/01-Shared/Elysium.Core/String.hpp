/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_STRING
#define ELYSIUM_CORE_STRING

#ifndef ELYSIUM_CORE_EXPORT
#include "Export.hpp"
#endif

#ifdef UNICODE
#define ElysiumChar wchar_t
#else
#define ElysiumChar char
#endif 

namespace Elysium
{
	namespace Core
	{
		class EXPORT String
		{
		public:
			String(const ElysiumChar* Value);
			~String();
		private:
			size_t _Length;
			ElysiumChar* _Data;
		};
	}
}
#endif
