/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_STRING
#define ELYSIUM_CORE_STRING

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_STRING
#include "../Elysium.Core.Template/String.hpp"
#endif

namespace Elysium::Core
{
	//using Utf8String = Elysium::Core::Template::Text::Utf8String();

	/*
	ToDos:
	- empty/null string as static instance where every empty/null string references it internally
	- strings on stack if small enough
	- ToCharArray() -> Array<char8_t> with copied values
	- possibly get rid of \0 (will have to think this one through first)
	*/
	
	namespace Collections::Template
	{
		template <typename T>
		class List;
	}

	class ELYSIUM_CORE_API Utf8String final
	{
	public:
		using Character = char8_t;
		using ConstCharacter = const char8_t;
		using CharacterPointer = char8_t*;
		using ConstCharacterPointer = const char8_t*;
		using CharacterReference = char8_t&;
		using ConstCharacterReference = const char8_t&;
	public:
		Utf8String();
		Utf8String(const Elysium::Core::size Length);
		Utf8String(ConstCharacterPointer Value);
		Utf8String(ConstCharacterPointer Value, const Elysium::Core::size Length);
		Utf8String(const Utf8String& Source);
		Utf8String(Utf8String&& Right) noexcept;
		~Utf8String();

		Utf8String& operator=(ConstCharacterPointer Value);
		Utf8String& operator=(const Utf8String& Source);
		Utf8String& operator=(Utf8String&& Right) noexcept;

		const bool operator==(const Utf8String& Other) const;
		const bool operator!=(const Utf8String& Other) const;
		const bool operator<(const Utf8String& Other) const;
		const bool operator>(const Utf8String& Other) const;
		const bool operator<=(const Utf8String Other) const;
		const bool operator>=(const Utf8String& Other) const;

		const bool operator==(const char8_t* Other) const;
		const bool operator!=(const char8_t* Other) const;

		CharacterReference operator[](const Elysium::Core::size Index);
		ConstCharacterReference operator[](const Elysium::Core::size Index) const;

		Elysium::Core::size GetHashCode() const;
		const Elysium::Core::size GetLength() const;
		
		const Elysium::Core::size IndexOf(ConstCharacter Value) const;
		const Elysium::Core::size IndexOf(ConstCharacter Value, const Elysium::Core::size StartIndex) const;
		const Elysium::Core::size IndexOf(ConstCharacterPointer Value) const;
		const Elysium::Core::size IndexOf(ConstCharacterPointer Value, const Elysium::Core::size StartIndex) const;
		const Elysium::Core::size IndexOf(const Utf8String& Value, const Elysium::Core::size StartIndex) const;

		const Elysium::Core::size LastIndexOf(ConstCharacter Value) const;
		const Elysium::Core::size LastIndexOf(ConstCharacterPointer Value) const;
		const Elysium::Core::size LastIndexOf(ConstCharacterPointer Value, const Elysium::Core::size StartIndex) const;
		const Elysium::Core::size LastIndexOf(const Utf8String& Value, const Elysium::Core::size StartIndex) const;

		//List<String> Split(const char8_t Delimiter) const;

		void Split(ConstCharacter Delimiter, Collections::Template::List<Utf8String>& Target) const;
		void Split(ConstCharacterPointer Delimiter, Collections::Template::List<Utf8String>& Target) const;

		const bool StartsWith(ConstCharacterPointer Value) const;

		const bool EndsWith(ConstCharacterPointer Value) const;

		//Collections::Template::String Replace(const char8_t OldCharacter, const char8_t NewCharacter);

		Utf8String Substring(const Elysium::Core::size StartIndex) const;
		Utf8String Substring(const Elysium::Core::size StartIndex, const Elysium::Core::size Length) const;

		//String ToLower();
		//String ToUpper();

		//String UnsafeSubstring(const Elysium::Core::size StartIndex) const;
		//String UnsafeSubstring(const Elysium::Core::size StartIndex, const Elysium::Core::size Length) const;
		
		static const Utf8String Empty;

		static const bool IsNull(const Utf8String& Value);
		static const bool IsEmpty(const Utf8String& Value);
		static const bool IsNullOrEmtpy(const Utf8String& Value);
	private:
		Elysium::Core::size _Length;
		CharacterPointer _Data;
	};
}
#endif
