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

#ifndef ELYSIUM_CORE_COLLECTIONS_GENERIC_LIST
#include "List.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		class ELYSIUM_CORE_API StringView final
		{
		public:
			StringView();
			StringView(ElysiumChar* Input);
			StringView(ElysiumChar* Input, size_t Length);
			StringView(const Elysium::Core::String* Input);
			StringView(const Elysium::Core::String* Input, size_t Length);
			StringView(const Elysium::Core::String* Input, size_t Offset, size_t Length);
			StringView(const StringView& Value);
			~StringView();

			void Split(const ElysiumChar Delimiter, Elysium::Core::Collections::Generic::List<StringView>* Views);
			void Split(const ElysiumChar* Delimiter, Elysium::Core::Collections::Generic::List<StringView>* Views);

			// assignment operators
			StringView& operator=(const StringView& Value);

			// cast operators
			operator Elysium::Core::String() const;
		private:
			ElysiumChar* _Data;
			size_t _Length;
		};
	}
}
#endif
