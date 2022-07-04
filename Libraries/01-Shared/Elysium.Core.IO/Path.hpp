/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_IO_PATH
#define ELYSIUM_CORE_IO_PATH

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "../Elysium.Core/API.hpp"
#endif

#ifndef ELYSIUM_CORE_ARGUMENTEXCEPTION
#include "../Elysium.Core/ArgumentException.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONCEPTS_UTF8STRINGCONTAINER
#include "../Elysium.Core.Template/Utf8StringContainer.hpp"
#endif

namespace Elysium::Core::IO
{
	class ELYSIUM_CORE_API Path
	{
	public:
		Path() = delete;

		Path(const Path& Source) = delete;

		Path(Path&& Right) noexcept = delete;

		~Path() = delete;
	public:
		Path& operator=(const Path& Source) = delete;

		Path& operator=(Path&& Right) noexcept = delete;
	public:
		/// <summary>
		/// 
		/// </summary>
		inline static constexpr Elysium::Core::Utf8String::ConstCharacter DirectorySeparator = u8'\\';

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr Elysium::Core::Utf8String::ConstCharacter AlternativeDirectorySeparator = u8'/';

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr Elysium::Core::Utf8String::ConstCharacter PathSeparator = u8'.';

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr Elysium::Core::Utf8String::ConstCharacter VolumeSeparator = u8':';

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr Elysium::Core::Utf8String::ConstCharacter InvalidFileNameCharacters[] =
		{
			// ASCII NUL
			0x00,

			// control characters (1 - 31)
			0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
			0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
			0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
			0x1F,

			// further invalid characters
			u8'"', u8'*', u8'/', u8':', u8'<', u8'>', u8'?', u8'\\', u8'|'
		};

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr Elysium::Core::Utf8String::ConstCharacter InvalidPathCharacters[] =
		{
			// ASCII NUL
			0x00,

			// control characters (1 - 31)
			0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
			0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 
			0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
			0x1F,

			// further invalid characters
			u8'"', u8'<', u8'>', u8'\\', u8'|'
		};

		/// <summary>
		/// 
		/// </summary>
		inline static constexpr Elysium::Core::Utf8String::ConstCharacter WildcardCharacters[] =
		{
			u8'*', u8'?'
		};
	public:
		template<Elysium::Core::Template::Concepts::Utf8StringContainer T>
		static Elysium::Core::Utf8String GetDirectoryName(const T& Path);

		template<Elysium::Core::Template::Concepts::Utf8StringContainer T>
		static Elysium::Core::Utf8String GetFullPath(const T& Path);

		template<Elysium::Core::Template::Concepts::Utf8StringContainer T>
		static Elysium::Core::Utf8String GetFullPath(const T& Path, const T& BasePath);
	private:
		template<Elysium::Core::Template::Concepts::Utf8StringContainer T>
		static void Validate(const T& Path, const bool ValidateWildcards);

		static Elysium::Core::Utf8String GetFullPath(const char* ASCIIPath);
	};

	template<Elysium::Core::Template::Concepts::Utf8StringContainer T>
	inline Elysium::Core::Utf8String Path::GetDirectoryName(const T& Path)
	{
		Validate(Path, false);

		const Elysium::Core::Template::System::size IndexOfPathSeparator = Path.LastIndexOf(PathSeparator);
		if (IndexOfPathSeparator == static_cast<Elysium::Core::Template::System::size>(-1))
		{

		}
		else
		{

		}

		// ToDo:
		throw 1;
	}

	template<Elysium::Core::Template::Concepts::Utf8StringContainer T>
	inline Elysium::Core::Utf8String Path::GetFullPath(const T& Path)
	{
		Validate(Path, false);

		return GetFullPath((char*)&Path[0]);
	}

	template<Elysium::Core::Template::Concepts::Utf8StringContainer T>
	inline Elysium::Core::Utf8String Path::GetFullPath(const T& Path, const T& BasePath)
	{
		Validate(Path, false);
		Validate(BasePath, false);

		throw 1;
	}

	template<Elysium::Core::Template::Concepts::Utf8StringContainer T>
	inline void Path::Validate(const T& Path, const bool ValidateWildcards)
	{
		if (Path.GetLength() == 0)
		{
			throw ArgumentException(u8"Path");
		}

		if (Path.IndexOfAny(&InvalidPathCharacters[0], 36) != static_cast<Elysium::Core::Template::System::size>(-1) ||
			(ValidateWildcards && Path.IndexOfAny(&WildcardCharacters[0], 2) != static_cast<Elysium::Core::Template::System::size>(-1)))
		{
			throw ArgumentException(u8"Path contains illegal characters.");
		}
	}
}
#endif
