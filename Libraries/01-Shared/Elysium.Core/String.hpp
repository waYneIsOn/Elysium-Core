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

#ifndef ELYSIUM_CORE_CHAR
#include "Char.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
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
	public:
		String();
		String(const size_t Length);
		String(ConstCharacterPointer Value);
		String(ConstCharacterPointer Value, const size_t Length);
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

		char8_t& operator[](const size_t Index);
		const char8_t& operator[](const size_t Index) const;

		const Elysium::Core::int32_t GetHashCode() const;
		const size_t GetLength() const;
		
		const size_t IndexOf(ConstCharacter Value) const;
		const size_t IndexOf(ConstCharacter Value, const size_t StartIndex) const;
		const size_t IndexOf(ConstCharacterPointer Value) const;
		const size_t IndexOf(ConstCharacterPointer Value, const size_t StartIndex) const;
		const size_t IndexOf(const String& Value, const size_t StartIndex) const;

		const size_t LastIndexOf(ConstCharacter Value) const;
		const size_t LastIndexOf(ConstCharacterPointer Value) const;
		const size_t LastIndexOf(ConstCharacterPointer Value, const size_t StartIndex) const;
		const size_t LastIndexOf(const String& Value, const size_t StartIndex) const;

		//List<String> Split(const char8_t Delimiter) const;

		void Split(ConstCharacter Delimiter, Collections::Template::List<String>& Target) const;
		void Split(ConstCharacterPointer Delimiter, Collections::Template::List<String>& Target) const;

		const bool StartsWith(ConstCharacterPointer Value) const;

		const bool EndsWith(ConstCharacterPointer Value) const;

		//Collections::Template::String Replace(const char8_t OldCharacter, const char8_t NewCharacter);

		String Substring(const size_t StartIndex) const;
		String Substring(const size_t StartIndex, const size_t Length) const;

		//String ToLower();
		//String ToUpper();

		//String UnsafeSubstring(const size_t StartIndex) const;
		//String UnsafeSubstring(const size_t StartIndex, const size_t Length) const;
		
		static const String Empty;
		static const char8_t NullTerminationChar = u8'\0';
		
		static const bool IsNull(const String& Value);
		static const bool IsEmpty(const String& Value);
		static const bool IsNullOrEmtpy(const String& Value);
	private:
		size_t _Length;
		CharacterPointer _Data;
	};
}
#endif
