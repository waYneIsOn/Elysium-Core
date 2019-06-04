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
		namespace Text
		{
			class Encoding;
		}

		class EXPORT String : public Elysium::Core::Collections::IEnumerable<ElysiumChar>
		{
			friend class Text::Encoding;
		public:
			String();
			String(size_t Length);
			String(const ElysiumChar* Value);
			String(const ElysiumChar* Value, size_t Length);
			String(const String& Value);
			~String();

			// properties - getter
			const size_t GetLength() const;
			const ElysiumChar* GetCharArray() const;

			// operators
			virtual String& operator=(const ElysiumChar* Value);
			virtual ElysiumChar& operator[](size_t Index) const;

			// ...
			static bool IsNullOrEmtpy(const String& Value);

			// methods
			void Substring(size_t StartIndex, String* Result) const;
			void Substring(size_t StartIndex, size_t Length, String* Result) const;
			//void ToLower(String* Result);
			//void ToUpper(String* Result);
		private:
			size_t _Length;	// ATTENTION: this is the number Of ElysiumChars - not the number of bytes!
			ElysiumChar* _Data;
		};
	}
}
#endif
