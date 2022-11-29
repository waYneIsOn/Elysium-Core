/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_OBJECT
#define ELYSIUM_CORE_OBJECT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_GLOBALIZATION_NUMBERFORMATINFO
#include "../Elysium.Core.Globalization/NumberFormatInfo.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_APPDOMAIN
#include "../Elysium.Core.Reflection/AppDomain.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "../Elysium.Core.Reflection/Type.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_REMOVEREFERENCE
#include "../Elysium.Core.Template/RemoveReference.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TEXT_CONVERT
#include "../Elysium.Core.Template/Convert.hpp"
#endif

#ifndef _TYPEINFO_
#include <typeinfo>
#endif

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Object final
	{
	public:
		Object() = delete;

		Object(const Object& Source) = delete;

		Object(Object&& Right) noexcept = delete;

		~Object() = delete;
	public:
		Object& operator=(const Object& Source) = delete;

		Object& operator=(Object&& Right) noexcept = delete;
	public:
		template <class T>
		static const Elysium::Core::Reflection::Type& GetType();

		template <class T>
		static const Elysium::Core::Reflection::Type& GetType(const T Value);
		
		template <class T>
		static const Elysium::Core::Utf8String ToUtf8String(const T Value);

		template <class T>
		static const Elysium::Core::Utf8String ToUtf8String(const T Value, const Globalization::Utf8NumberFormatInfo& FormatInfo);
	};

	template<class T>
	inline const Elysium::Core::Reflection::Type& Object::GetType()
	{
		const Elysium::Core::size TypeId = typeid(T).hash_code();

		// ToDo: lookup TypeId in AppDomain
		//Elysium::Core::Reflection::AppDomain::GetCurrentDomain().
		throw 1;
	}

	template<class T>
	inline const Elysium::Core::Reflection::Type& Object::GetType(const T Value)
	{
		const Elysium::Core::size TypeId = typeid(Value).hash_code();

		// ToDo: lookup TypeId in AppDomain
		//Elysium::Core::Reflection::AppDomain::GetCurrentDomain().
		throw 1;
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<Elysium::Core::int8_t>(const Elysium::Core::int8_t Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}
	
	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<Elysium::Core::int16_t>(const Elysium::Core::int16_t Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<Elysium::Core::int32_t>(const Elysium::Core::int32_t Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<Elysium::Core::int64_t>(const Elysium::Core::int64_t Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<Elysium::Core::uint8_t>(const Elysium::Core::uint8_t Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<Elysium::Core::uint16_t>(const Elysium::Core::uint16_t Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<Elysium::Core::uint32_t>(const Elysium::Core::uint32_t Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<Elysium::Core::uint64_t>(const Elysium::Core::uint64_t Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<float>(const float Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::Utf8String Object::ToUtf8String<double>(const double Value)
	{
		return Elysium::Core::Template::Text::Convert<char8_t>::ToString(Value, 10);
	}

	template <class T>
	inline const Elysium::Core::Utf8String Object::ToUtf8String(const T Value)
	{
		return Value.ToUtf8String();
	}

	template<class T>
	inline const Elysium::Core::Utf8String Object::ToUtf8String(const T Value, const Globalization::Utf8NumberFormatInfo& FormatInfo)
	{
		return Value.ToUtf8String(FormatInfo);
	}
}
#endif
