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
		StringView(char8_t* Input, Elysium::Core::size Length);
		StringView(const String& Input);
		StringView(const String& Input, Elysium::Core::size Length);
		StringView(const String& Input, Elysium::Core::size Offset, Elysium::Core::size Length);
		StringView(const StringView& Source);
		StringView(StringView&& Right) noexcept;
		~StringView();

		StringView& operator=(const StringView& Source);
		StringView& operator=(StringView&& Right) noexcept;

		char8_t& operator[](Elysium::Core::size Index);
		const char8_t& operator[](Elysium::Core::size Index) const;

		operator Elysium::Core::String() const;

		const bool operator==(const StringView& Other) const;
		const bool operator!=(const StringView& Other) const;
		const bool operator<(const StringView& Other) const;
		const bool operator>(const StringView& Other) const;
		const bool operator<=(const StringView& Other) const;
		const bool operator>=(const StringView& Other) const;

		const bool operator==(const String& Other) const;

		const Elysium::Core::size GetLength() const;

		const Elysium::Core::size IndexOf(const char8_t Value) const;
		const Elysium::Core::size IndexOf(const char8_t Value, const Elysium::Core::size StartIndex) const;
		const Elysium::Core::size IndexOf(const char8_t* Value) const;
		const Elysium::Core::size IndexOf(const char8_t* Value, const Elysium::Core::size StartIndex) const;
		const Elysium::Core::size IndexOf(const String& Value, const Elysium::Core::size StartIndex) const;

		const Elysium::Core::size LastIndexOf(const char8_t* Value) const;

		void Split(const char8_t Delimiter, Collections::Template::List<StringView>& Views) const;
		void Split(const char8_t* Delimiter, Collections::Template::List<StringView>& Views) const;

		StringView Substringview(const Elysium::Core::size StartIndex) const;
		StringView Substringview(const Elysium::Core::size StartIndex, const Elysium::Core::size Length) const;
	private:
		Elysium::Core::size _Length;
		char8_t* _Data;
	};
}
#endif
