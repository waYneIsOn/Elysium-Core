/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_STRINGVIEW
#define ELYSIUM_CORE_STRINGVIEW

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API StringView final
		{
		public:
			StringView();
			StringView(const String& Input, size_t Length);
			~StringView();

			// properties - getter
			const ElysiumChar* GetData() const;
			const size_t GetLength() const;
		private:
			const ElysiumChar* _Data;
			const size_t _Length;
		};
	}
}
#endif
