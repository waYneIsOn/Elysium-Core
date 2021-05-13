/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_STRINGVIEW
#define ELYSIUM_CORE_STRINGVIEW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API StringView final
	{
	public:
		StringView();
		StringView(char8_t* Input);
		StringView(char8_t* Input, size_t Length);
		StringView(const String& Input);
		StringView(const String& Input, size_t Length);
		StringView(const String& Input, size_t Offset, size_t Length);
		StringView(const StringView& Source);
		StringView(StringView&& Right) noexcept;
		~StringView();

		StringView& operator=(const StringView& Source);
		StringView& operator=(StringView&& Right) noexcept;

		char8_t& operator[](size_t Index);
		const char8_t& operator[](size_t Index) const;

		operator Elysium::Core::String() const;

		const bool operator==(const StringView& Other) const;
		const bool operator!=(const StringView& Other) const;
		const bool operator<(const StringView& Other) const;
		const bool operator>(const StringView& Other) const;
		const bool operator<=(const StringView& Other) const;
		const bool operator>=(const StringView& Other) const;

		const bool operator==(const String& Other) const;

		const size_t GetLength() const;

		const size_t IndexOf(const char8_t Value) const;
		const size_t IndexOf(const char8_t Value, const size_t StartIndex) const;
		const size_t IndexOf(const char8_t* Value) const;
		const size_t IndexOf(const char8_t* Value, const size_t StartIndex) const;
		const size_t IndexOf(const String& Value, const size_t StartIndex) const;

		const size_t LastIndexOf(const char8_t* Value) const;

		void Split(const char8_t Delimiter, Collections::Template::List<StringView>& Views) const;
		void Split(const char8_t* Delimiter, Collections::Template::List<StringView>& Views) const;

		StringView Substringview(const size_t StartIndex) const;
		StringView Substringview(const size_t StartIndex, const size_t Length) const;
	private:
		size_t _Length;
		char8_t* _Data;

		static constexpr const char8_t _NullTerminationChar = u8'\0';
	};
}
#endif
