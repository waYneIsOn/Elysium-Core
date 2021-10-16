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
#include "../Elysium.Core.Template/Primitives.hpp"
#endif

namespace Elysium::Core
{
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

	class ELYSIUM_CORE_API String final
	{
	public:
		using Character = char8_t;
		using ConstCharacter = const char8_t;
		using CharacterPointer = char8_t*;
		using ConstCharacterPointer = const char8_t*;
		using CharacterReference = char8_t&;
		using ConstCharacterReference = const char8_t&;
	public:
		String();
		String(const Elysium::Core::size Length);
		String(ConstCharacterPointer Value);
		String(ConstCharacterPointer Value, const Elysium::Core::size Length);
		String(const String& Source);
		String(String&& Right) noexcept;
		~String();

		String& operator=(ConstCharacterPointer Value);
		String& operator=(const String& Source);
		String& operator=(String&& Right) noexcept;

		const bool operator==(const String& Other) const;
		const bool operator!=(const String& Other) const;
		const bool operator<(const String& Other) const;
		const bool operator>(const String& Other) const;
		const bool operator<=(const String Other) const;
		const bool operator>=(const String& Other) const;

		CharacterReference operator[](const Elysium::Core::size Index);
		ConstCharacterReference operator[](const Elysium::Core::size Index) const;

		const Elysium::Core::int32_t GetHashCode() const;
		const Elysium::Core::size GetLength() const;
		
		const Elysium::Core::size IndexOf(ConstCharacter Value) const;
		const Elysium::Core::size IndexOf(ConstCharacter Value, const Elysium::Core::size StartIndex) const;
		const Elysium::Core::size IndexOf(ConstCharacterPointer Value) const;
		const Elysium::Core::size IndexOf(ConstCharacterPointer Value, const Elysium::Core::size StartIndex) const;
		const Elysium::Core::size IndexOf(const String& Value, const Elysium::Core::size StartIndex) const;

		const Elysium::Core::size LastIndexOf(ConstCharacter Value) const;
		const Elysium::Core::size LastIndexOf(ConstCharacterPointer Value) const;
		const Elysium::Core::size LastIndexOf(ConstCharacterPointer Value, const Elysium::Core::size StartIndex) const;
		const Elysium::Core::size LastIndexOf(const String& Value, const Elysium::Core::size StartIndex) const;

		//List<String> Split(const char8_t Delimiter) const;

		void Split(ConstCharacter Delimiter, Collections::Template::List<String>& Target) const;
		void Split(ConstCharacterPointer Delimiter, Collections::Template::List<String>& Target) const;

		const bool StartsWith(ConstCharacterPointer Value) const;

		const bool EndsWith(ConstCharacterPointer Value) const;

		//Collections::Template::String Replace(const char8_t OldCharacter, const char8_t NewCharacter);

		String Substring(const Elysium::Core::size StartIndex) const;
		String Substring(const Elysium::Core::size StartIndex, const Elysium::Core::size Length) const;

		//String ToLower();
		//String ToUpper();

		//String UnsafeSubstring(const Elysium::Core::size StartIndex) const;
		//String UnsafeSubstring(const Elysium::Core::size StartIndex, const Elysium::Core::size Length) const;
		
		static const String Empty;
		static const Character NullTerminationChar = u8'\0';
		
		static const bool IsNull(const String& Value);
		static const bool IsEmpty(const String& Value);
		static const bool IsNullOrEmtpy(const String& Value);
	private:
		Elysium::Core::size _Length;
		CharacterPointer _Data;
	};
}
#endif
