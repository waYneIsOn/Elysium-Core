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
		String();
		String(const size_t Length);
		String(const char8_t* Value);
		String(const char8_t* Value, const size_t Length);
		String(const String& Source);
		String(String&& Right) noexcept;
		~String();

		String& operator=(const char8_t* Value);
		String& operator=(const String& Source);
		String& operator=(String&& Right) noexcept;

		bool operator==(const String& Other) const;
		bool operator!=(const String& Other) const;
		bool operator<(const String& Other) const;
		bool operator>(const String& Other) const;
		bool operator<=(const String Other) const;
		bool operator>=(const String& Other) const;

		char8_t& operator[](const size_t Index) const;

		const size_t GetLength() const throw();
		
		const size_t IndexOf(const char8_t Value) const;
		const size_t IndexOf(const char8_t Value, const size_t StartIndex) const;
		const size_t IndexOf(const char8_t* Value) const;
		const size_t IndexOf(const char8_t* Value, const size_t StartIndex) const;
		const size_t IndexOf(const String& Value, const size_t StartIndex) const;
		
		const size_t LastIndexOf(const char8_t* Value) const;
		const size_t LastIndexOf(const char8_t* Value, const size_t StartIndex) const;
		const size_t LastIndexOf(const String& Value, const size_t StartIndex) const;

		//List<String> Split(const char8_t Delimiter) const;

		void Split(const char8_t Delimiter, Collections::Template::List<String>& Target) const;
		void Split(const char8_t* Delimiter, Collections::Template::List<String>& Target) const;

		const bool StartsWith(const char8_t* Value) const;

		const bool EndsWith(const char8_t* Value) const;

		//Collections::Template::String Replace(const char8_t OldCharacter, const char8_t NewCharacter);

		String Substring(const size_t StartIndex) const;
		String Substring(const size_t StartIndex, const size_t Length) const;

		//String ToLower();
		//String ToUpper();
		
		static const String Empty;
		
		static const bool IsNull(const String& Value);
		static const bool IsEmpty(const String& Value);
		static const bool IsNullOrEmtpy(const String& Value);
	private:
		size_t _Length;
		char8_t* _Data;

		static constexpr const char8_t _NullTerminationChar = u8'\0';
	};
}
#endif
