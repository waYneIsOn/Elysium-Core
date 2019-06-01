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

#ifndef ELYSIUM_CORE_COLLECTIONS_IENUMERABLE
#include "IEnumerable.hpp"
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
		class EXPORT String : public Elysium::Core::Collections::IEnumerable<ElysiumChar>
		{
		public:
			String(const ElysiumChar* Value);
			String(const ElysiumChar* Value, size_t Length);
			String(const String& Value);
			~String();

			// properties - getter
			const size_t GetLength() const;

			// operators
			virtual ElysiumChar& operator[](size_t Index) const;

			static bool IsNullOrEmtpy(const String& Value);

			const ElysiumChar* ToCharArray() const;
		private:
			String(size_t Length);

			size_t _Length;	// ATTENTION: this is the number Of ElysiumChars - not the number of bytes!
			ElysiumChar* _Data;
		};
	}
}
#endif
