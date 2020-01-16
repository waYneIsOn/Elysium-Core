/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_CONVERT
#define ELYSIUM_CORE_CONVERT

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
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

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Convert final
	{
	public:
		~Convert();

		static String ToString(const uint32_t Value, const int32_t FromBase);
		static String ToString(const int32_t Value, const int32_t FromBase);
		static String ToString(const int64_t Value, const int32_t FromBase);
		static String ToString(const size_t Value, const int32_t FromBase);
		static String ToString(const float Value, const int32_t FromBase);
		static String ToString(const double Value, const int32_t FromBase);

		static String ToBase64String(Elysium::Core::Collections::Template::List<Elysium::Core::byte> Bytes);

		static int32_t ToInt32(const char16_t* Value, const int32_t FromBase);
		static int32_t ToInt32(const Elysium::Core::String& Value, const int32_t FromBase);

		static float ToSingle(const char16_t* Value);
		static float ToSingle(const Elysium::Core::String& Value);
	private:
		Convert();
	};
}
#endif
