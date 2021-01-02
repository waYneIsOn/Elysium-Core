/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_CONVERT
#define ELYSIUM_CORE_CONVERT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO
#include "NumberFormatInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_LIST
#include "List.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "StringView.hpp"
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Convert final
	{
	public:
		Convert() = delete;
		Convert(const Convert& Source) = delete;
		Convert(Convert&& Right) noexcept = delete;
		~Convert() = delete;

		Convert& operator=(const Convert& Source) = delete;
		Convert& operator=(Convert&& Right) noexcept = delete;

		static const Elysium::Core::String ToString(const Elysium::Core::int16_t Value, const Elysium::Core::int32_t FromBase);
		static const Elysium::Core::String ToString(const Elysium::Core::int32_t Value, const Elysium::Core::int32_t FromBase);
		static const Elysium::Core::String ToString(const Elysium::Core::int64_t Value, const Elysium::Core::int32_t FromBase);
		static const Elysium::Core::String ToString(const Elysium::Core::uint16_t Value, const Elysium::Core::int32_t FromBase);
		static const Elysium::Core::String ToString(const Elysium::Core::uint32_t Value, const Elysium::Core::int32_t FromBase);
		static const Elysium::Core::String ToString(const Elysium::Core::uint64_t Value, const Elysium::Core::int32_t FromBase);
		static const Elysium::Core::String ToString(const float Value, const Elysium::Core::int32_t FromBase);
		static const Elysium::Core::String ToString(const double Value, const Elysium::Core::int32_t FromBase);

		static Elysium::Core::Collections::Template::List<Elysium::Core::byte> FromBase64String(const String& Base64String);
		static Elysium::Core::String ToBase64String(const Elysium::Core::byte* Bytes, const Elysium::Core::uint32_t Length);

		static Elysium::Core::int32_t ToInt32(const char8_t* Value, const size_t Length, const Elysium::Core::int32_t FromBase);
		static Elysium::Core::int32_t ToInt32(const Elysium::Core::String& Value, const Elysium::Core::int32_t FromBase);
		static Elysium::Core::int32_t ToInt32(const Elysium::Core::StringView& Value, const Elysium::Core::int32_t FromBase);

		static Elysium::Core::uint16_t ToUInt16(const char8_t* Value, const Elysium::Core::int32_t FromBase);

		static Elysium::Core::uint8_t ToUInt8(const char8_t* Value, const Elysium::Core::int32_t FromBase);

		static float ToSingle(const char8_t* Value);
		static float ToSingle(const Elysium::Core::String& Value);
	private:
		static const String _Base64Chars;

		static const Elysium::Core::int32_t ToInt32FromDec(const char8_t* Value, const size_t Length);
		static const Elysium::Core::int32_t ToInt32FromHex(const char8_t* Value, const size_t Length);

		static const Elysium::Core::uint32_t ToUInt32FromHex(const char8_t* Value, const size_t Length);

		static bool IsBase64(const char8_t Char);
	};
}
#endif
