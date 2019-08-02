/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_CHARENUMERATOR
#define ELYSIUM_CORE_CHARENUMERATOR

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_IENUMERATOR
#include "IEnumerator.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API CharEnumerator final : public Elysium::Core::Collections::Generic::IEnumerator<ElysiumChar>
		{
		public:
			CharEnumerator(const String* IEnumerable);
			~CharEnumerator();

			virtual bool MoveNext() override;
		private:
			const String* _IEnumerable;
			size_t _Index;
		};
	}
}
#endif
