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

#ifndef ELYSIUM_CORE_CONVERT
#include "Convert.hpp"
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

namespace Elysium::Core
{
	class ELYSIUM_CORE_API Object final
	{
	public:
		Object() = delete;
		Object(const Object& Source) = delete;
		Object(Object&& Right) noexcept = delete;
		~Object() = delete;

		Object& operator=(const Object& Source) = delete;
		Object& operator=(Object&& Right) noexcept = delete;
		/*
		template <class T>
		static constexpr T&& Move(T& Value) noexcept;
		*/
		template <class T>
		static const Elysium::Core::int32_t GetHashCode(const T Value);

		template <class T>
		static const Elysium::Core::String ToString(const T Value);
	};

	template<>
	inline const Elysium::Core::int32_t Object::GetHashCode<Elysium::Core::int8_t>(const Elysium::Core::int8_t Value)
	{
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	template<>
	inline const Elysium::Core::int32_t Object::GetHashCode<Elysium::Core::int16_t>(const Elysium::Core::int16_t Value)
	{
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	template<>
	inline const Elysium::Core::int32_t Object::GetHashCode<Elysium::Core::int32_t>(const Elysium::Core::int32_t Value)
	{
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	template<>
	inline const Elysium::Core::int32_t Object::GetHashCode<Elysium::Core::int64_t>(const Elysium::Core::int64_t Value)
	{
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	template<>
	inline const Elysium::Core::int32_t Object::GetHashCode<Elysium::Core::uint8_t>(const Elysium::Core::uint8_t Value)
	{
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	template<>
	inline const Elysium::Core::int32_t Object::GetHashCode<Elysium::Core::uint16_t>(const Elysium::Core::uint16_t Value)
	{
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	template<>
	inline const Elysium::Core::int32_t Object::GetHashCode<Elysium::Core::uint32_t>(const Elysium::Core::uint32_t Value)
	{
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	template<>
	inline const Elysium::Core::int32_t Object::GetHashCode<Elysium::Core::uint64_t>(const Elysium::Core::uint64_t Value)
	{
		return static_cast<Elysium::Core::int32_t>(Value);
	}

	template<class T>
	inline const Elysium::Core::int32_t Object::GetHashCode(const T Value)
	{
		return Value.GetHashCode();
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::int8_t>(const Elysium::Core::int8_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::int16_t>(const Elysium::Core::int16_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::int32_t>(const Elysium::Core::int32_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::int64_t>(const Elysium::Core::int64_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::uint8_t>(const Elysium::Core::uint8_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::uint16_t>(const Elysium::Core::uint16_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::uint32_t>(const Elysium::Core::uint32_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::uint64_t>(const Elysium::Core::uint64_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<float>(const float Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<double>(const double Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10, Globalization::NumberFormatInfo::GetCurrentInfo());
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::String>(const Elysium::Core::String Value)
	{
		return Value;
	}

	template <class T>
	inline const Elysium::Core::String Object::ToString(const T Value)
	{
		return Value.ToString();
	}
}
#endif
