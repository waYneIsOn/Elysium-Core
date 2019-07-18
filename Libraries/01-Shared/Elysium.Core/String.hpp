/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_STRING
#define ELYSIUM_CORE_STRING

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_IENUMERABLE
#include "IEnumerable.hpp"
#endif

#ifdef UNICODE
#define ElysiumChar wchar_t
#define ElysiumStringLength wcslen
#else
#define ElysiumChar char
#define ElysiumStringLength strlen
#endif 

namespace Elysium
{
	namespace Core
	{
		namespace Text
		{
			class Encoding;
		}

		class ELYSIUM_CORE_API String : public Elysium::Core::Collections::IEnumerable<ElysiumChar>
		{
			friend class Text::Encoding;
		public:
			String();
			String(size_t Length);
			String(const ElysiumChar* Value);
			String(const ElysiumChar* Value, size_t Length);
			String(const String& Value);
			String(String&& Right);
			~String();

			// properties - getter
			const size_t GetLength() const;
			const ElysiumChar* GetCharArray() const;

			// methods
			size_t IndexOf(const ElysiumChar Value) const;
			size_t IndexOf(const ElysiumChar Value, const size_t StartIndex) const;
			size_t IndexOf(const ElysiumChar* Value) const;
			size_t IndexOf(const ElysiumChar* Value, const size_t StartIndex) const;
			bool StartsWith(const ElysiumChar* Value) const;
			void Substring(size_t StartIndex, String* Result) const;
			void Substring(size_t StartIndex, size_t Length, String* Result) const;
			//void ToLower(String* Result);
			//void ToUpper(String* Result);

			// ...
			static bool IsNullOrEmtpy(const String& Value);
			//static void Concat(const unsigned int ArgumentCount, const String* Arguments[], String* Output);

			// move assignment operator
			String& operator=(String&& Right);

			// assignment operators
			virtual String& operator=(const ElysiumChar* Value);
			virtual String& operator=(const String& Value);

			// index operator
			virtual ElysiumChar& operator[](size_t Index) const;

			// relational operators
			bool operator==(const String& Other);
			bool operator!=(const String& Other);
			bool operator<(const String& Other);
			bool operator>(const String& Other);
			bool operator<=(const String& Other);
			bool operator>=(const String& Other);
		private:
			size_t _Length;	// ATTENTION: this is the number Of ElysiumChars - not the number of bytes!
			ElysiumChar* _Data;
		};

		ELYSIUM_CORE_API bool operator==(const String& Left, const String& Right);
		ELYSIUM_CORE_API bool operator!=(const String& Left, const String& Right);
		ELYSIUM_CORE_API bool operator<(const String& Left, const String& Right);
		ELYSIUM_CORE_API bool operator>(const String& Left, const String& Right);
		ELYSIUM_CORE_API bool operator<=(const String& Left, const String& Right);
		ELYSIUM_CORE_API bool operator>=(const String& Left, const String& Right);
	}
}
#endif
