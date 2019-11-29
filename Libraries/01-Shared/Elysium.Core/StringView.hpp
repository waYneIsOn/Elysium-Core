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
			StringView(char16_t* Input);
			StringView(char16_t* Input, size_t Length);
			StringView(const Elysium::Core::String& Input);
			StringView(const Elysium::Core::String& Input, size_t Length);
			StringView(const Elysium::Core::String& Input, size_t Offset, size_t Length);
			StringView(const StringView& Source);
			StringView(StringView&& Right) noexcept;
			~StringView();

			StringView& operator=(const StringView& Source);
			StringView& operator=(StringView&& Right) noexcept;

			bool operator==(const StringView& Other) const;
			bool operator!=(const StringView& Other) const;
			bool operator<(const StringView& Other) const;
			bool operator>(const StringView& Other) const;
			bool operator<=(const StringView& Other) const;
			bool operator>=(const StringView& Other) const;

			const size_t GetLength() const;

			size_t IndexOf(const char16_t Value) const;
			size_t IndexOf(const char16_t Value, const size_t StartIndex) const;
			size_t IndexOf(const char16_t* Value) const;
			size_t IndexOf(const char16_t* Value, const size_t StartIndex) const;
			size_t IndexOf(const String& Value, const size_t StartIndex) const;
			void Split(const char16_t Delimiter, Elysium::Core::Collections::Generic::List<StringView>& Views) const;
			void Split(const char16_t* Delimiter, Elysium::Core::Collections::Generic::List<StringView>& Views) const;

			// index operator
			virtual char16_t& operator[](size_t Index) const;

			// cast operators
			operator Elysium::Core::String() const;
		private:
			size_t _Length;
			char16_t* _Data;
		};
	}
}
#endif
