/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_JSON_JSONSERIALIZER
#define ELYSIUM_CORE_JSON_JSONSERIALIZER

#ifndef ELYSIUM_CORE_JSON_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_REFLECTION_TYPE
#include "../Elysium.Core.Reflection/Type.hpp"
#endif

namespace Elysium::Core::Json
{
	class ELYSIUM_CORE_JSON_API JsonSerializer final
	{
	public:
		JsonSerializer();
		JsonSerializer(const JsonSerializer& Source) = delete;
		JsonSerializer(JsonSerializer&& Right) noexcept = delete;
		~JsonSerializer();

		JsonSerializer& operator=(const JsonSerializer& Source) = delete;
		JsonSerializer& operator=(JsonSerializer&& Right) noexcept = delete;

		template <class T>
		const String Serialize(const T& Object);

		template <class T>
		T Deserialize(const String& Json);
	};

	template<class T>
	inline const String JsonSerializer::Serialize(const T & Object)
	{
		/*
		const Elysium::Core::Reflection::Type& ObjectType = typeof(T);
		ObjectType.GetPropertyInfos();
		*/
		return String();
	}

	template<class T>
	inline T JsonSerializer::Deserialize(const String & Json)
	{
		return T();
	}
}
#endif
