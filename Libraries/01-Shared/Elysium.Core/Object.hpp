/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

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

#ifndef ELYSIUM_CORE_STRING
#include "String.hpp"
#endif

#ifndef ELYSIUM_CORE_CONVERT
#include "Convert.hpp"
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
		
		template <class T>
		static const Elysium::Core::String ToString(const T Value);
	};

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::int8_t>(const Elysium::Core::int8_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::int16_t>(const Elysium::Core::int16_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::int32_t>(const Elysium::Core::int32_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::int64_t>(const Elysium::Core::int64_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::uint8_t>(const Elysium::Core::uint8_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::uint16_t>(const Elysium::Core::uint16_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::uint32_t>(const Elysium::Core::uint32_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<Elysium::Core::uint64_t>(const Elysium::Core::uint64_t Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<float>(const float Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template<>
	inline const Elysium::Core::String Object::ToString<double>(const double Value)
	{
		return Elysium::Core::Convert::ToString(Value, 10);
	}

	template <class T>
	inline const Elysium::Core::String Object::ToString(const T Value)
	{
		return Value.ToString();
	}
}
#endif
