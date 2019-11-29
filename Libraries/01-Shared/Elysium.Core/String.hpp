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

namespace Elysium
{
	namespace Core
	{
		namespace Text
		{
			class Encoding;
		}

		class ELYSIUM_CORE_API String : public Elysium::Core::Collections::IEnumerable<char16_t>
		{
			friend class Text::Encoding;
		public:
			String();
			String(size_t Length);
			String(const char16_t* Value);
			String(const char16_t* Value, size_t Length);
			String(const String& Source);
			String(String&& Right) noexcept;
			~String();

			String& operator=(const String& Source);
			String& operator=(String&& Right) noexcept;

			String& operator=(const char16_t* Value);

			char16_t& operator[](size_t Index) const;

			bool operator==(const String& Other) const;
			bool operator!=(const String& Other) const;
			bool operator<(const String& Other) const;
			bool operator>(const String& Other) const;
			bool operator<=(const String& Other) const;
			bool operator>=(const String& Other) const;

			// properties - getter
			const size_t GetLength() const;
			const char16_t* GetCharArray() const;

			// methods
			size_t IndexOf(const char16_t Value) const;
			size_t IndexOf(const char16_t Value, const size_t StartIndex) const;
			size_t IndexOf(const char16_t* Value) const;
			size_t IndexOf(const char16_t* Value, const size_t StartIndex) const;
			size_t IndexOf(const String& Value, const size_t StartIndex) const;
			bool StartsWith(const char16_t* Value) const;
			void Substring(size_t StartIndex, String* Result) const;
			void Substring(size_t StartIndex, size_t Length, String* Result) const;
			//void ToLower(String* Result);
			//void ToUpper(String* Result);

			// ...
			static bool IsNullOrEmtpy(const String& Value);
			//static void Concat(const unsigned int ArgumentCount, const String* Arguments[], String* Output);
		private:
			size_t _Length;
			char16_t* _Data;
		};
	}
}
#endif
